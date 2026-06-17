import 'dotenv/config'
import { Server, Socket } from "socket.io";
import jwt from "jsonwebtoken";
import { getDb, getUserFriends } from '../../prisma/init';
import { PrismaClient } from '../../prisma/generated/prisma/client';
import { registerChatHandlers } from '../socket/chatHandlers';
import { registerRaceHandlers } from '../socket/raceHandlers';
import { registerPetHandlers } from '../socket/petHandlers';

let prisma: PrismaClient;
export const onlineUsers = new Map<number, string>();

async function handleConnect(io: Server, socket: Socket, onlineUsers: Map<number, string>) {
    const userId = socket.data.user.userId;
    onlineUsers.set(userId, socket.id);
    prisma = getDb(prisma);
    try {
        const friends = await getUserFriends(prisma, userId);
        if (!friends) return;
        friends.forEach((friend) => {
            const friendSocketId = onlineUsers.get(friend.id);
            if (friendSocketId)
                io.to(friendSocketId).emit('friend:online', { userId });
        });
    } catch (err: any) {
        console.error('[ERROR] initSocket(): ', err.message);
        socket.emit('error', { message: 'something went wrong' });
    }
}

async function handleDisconnect(io: Server, socket: Socket, onlineUsers: Map<number, string>, reason?: string) {
    console.log(`[SOCKET] User ${socket.data.user.userId} disconnected`, reason ? `(${reason})` : '');
    const userId = socket.data.user.userId;
    prisma = getDb(prisma);
    onlineUsers.delete(userId);
    try {
        const friends = await getUserFriends(prisma, userId);
        if (!friends) return;
        friends.forEach((friend) => {
            const friendSocketId = onlineUsers.get(friend.id);
            if (friendSocketId)
                io.to(friendSocketId).emit('friend:offline', { userId });
        });
    } catch (err: any) {
        console.error('[ERROR] initSocket(): ', err.message);
        socket.emit('error', { message: 'something went wrong' });
    }
}

function handlePresenceRequest(socket: Socket, onlineUsers: Map<number, string>, payload: { friendIds: number[] }) {
    const onlineUserIds = payload.friendIds.filter(id => onlineUsers.has(id));
    socket.emit('friends:presence', { onlineUserIds });
}

export function initSocket(io: Server) {
    io.use((socket: Socket, next: (err?: Error) => void) => {
        const token = socket.handshake.auth.token;
        if (!token) return next(new Error('Unauthorized'));
        try {
            const decoded = jwt.verify(token, process.env.JWT_SECRET!) as { userId: number };
            socket.data.user = { userId: decoded.userId };
            next();
        } catch {
            next(new Error('Unauthorized'));
        }
    });

    io.on('connection', async (socket: Socket) => {
        const userId = socket.data.user.userId;
        console.log(`[SOCKET] User ${userId} connecté`);

        socket.join(`user:${userId}`);

        prisma = getDb(prisma);
        try {
            const unreadCounts = await prisma.conversation.findMany({
                where: {
                    participants: { some: { userId } },
                    messages: {
                        some: {
                            senderId: { not: userId },
                            readBy: { none: { userId } }
                        }
                    }
                },
                select: {
                    id: true,
                    _count: {
                        select: {
                            messages: {
                                where: {
                                    senderId: { not: userId },
                                    readBy: { none: { userId } }
                                }
                            }
                        }
                    }
                }
            });

            if (unreadCounts.length > 0) {
                socket.emit('unread:summary', unreadCounts.map((c: any) => ({
                    conversationId: c.id,
                    count: c._count.messages
                })));
            }
        } catch (err: any) {
            console.error('[ERROR] unread summary:', err.message);
        }

        await handleConnect(io, socket, onlineUsers);
        socket.on('disconnect', (reason: string) => handleDisconnect(io, socket, onlineUsers, reason));
        socket.on('friends:presence:request', (payload: { friendIds: number[] }) => handlePresenceRequest(socket, onlineUsers, payload));

		// Pet states handlers
		registerPetHandlers(io, socket);

        // Chat handlers
        registerChatHandlers(io, socket);
        // Race handlers
        registerRaceHandlers(io, socket);
    });
}