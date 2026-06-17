// socket/chatHandlers.ts
import { Server, Socket } from 'socket.io';
import { PrismaClient } from '../../prisma/generated/prisma/client';

const prisma = new PrismaClient();

export function registerChatHandlers(io: Server, socket: Socket) {
  const userId: number = socket.data.user.userId;

  // Rejoindre une conversation
  socket.on('conversation:join', async (conversationId: number) => {
    try {
      const participant = await prisma.conversationParticipant.findUnique({
        where: { userId_conversationId: { userId, conversationId } }
      });
      if (!participant) return socket.emit('error', 'Accès refusé');

      socket.join(`conv:${conversationId}`);

      const unreadMessages = await prisma.message.findMany({
        where: {
          conversationId,
          senderId: { not: userId },
          readBy: { none: { userId } }
        },
        select: { id: true }
      });

      if (unreadMessages.length > 0) {
        await prisma.messageRead.createMany({
          data: unreadMessages.map((m: { id: number }) => ({ userId, messageId: m.id })),
          skipDuplicates: true,
        });

        socket.to(`conv:${conversationId}`).emit('message:read', {
          conversationId,
          userId,
        });
      }
    } catch (err) {
      console.error('[SOCKET] conversation:join error:', err);
      socket.emit('error', 'Erreur serveur lors du join');
    }
  });

  // Envoyer un message
  socket.on('message:send', async (data: { conversationId: number; content: string }, ack) => {
    try {
      const participant = await prisma.conversationParticipant.findUnique({
        where: { userId_conversationId: { userId, conversationId: data.conversationId } }
      });
      if (!participant) return ack?.({ error: 'Accès refusé' });

      const message = await prisma.message.create({
        data: {
          content: data.content.trim(),
          senderId: userId,
          conversationId: data.conversationId,
          readBy: {
            create: { userId }
          }
        },
        include: { sender: { select: { id: true, username: true } } }
      });

      await prisma.conversation.update({
        where: { id: data.conversationId },
        data: { lastActivity: new Date() }
      });

      // Étape 3 anticipée : socket.to au lieu de io.to
      socket.to(`conv:${data.conversationId}`).emit('message:new', message);
      ack?.({ success: true, message });

    } catch (err) {
      console.error('[SOCKET] message:send error:', err);
      ack?.({ error: 'Erreur serveur lors de l\'envoi' });
    }
  });
}