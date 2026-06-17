// srcs/express/socket/raceHandlers.ts

import { Server, Socket } from 'socket.io';

// ─── Types ────────────────────────────────────────────────────────────────────

interface RacePlayer {
    id: string;
    name: string;
    progress: number;
    y: number;
    color: string;
    socketId: string;
    isLocal: boolean;
}

interface Room {
    roomId: string;
    players: RacePlayer[];
    spectators: string[];
    status: 'waiting' | 'countdown' | 'racing' | 'finished';
    countdownTimer?: ReturnType<typeof setInterval>;
}

// ─── State global ─────────────────────────────────────────────────────────────

const rooms = new Map<string, Room>();
const socketToRoom = new Map<string, string>(); // socketId → roomId, lookup O(1)

// ─── Helpers ──────────────────────────────────────────────────────────────────

function generateRoomId(): string {
    return Math.random().toString(36).substring(2, 8).toUpperCase();
}

function serializeRoom(room: Room) {
    return {
        roomId: room.roomId,
        players: room.players.map(({ socketId: _sid, ...p }) => p),
        status: room.status,
        spectatorCount: room.spectators.length,
    };
}

function findRoomBySocket(socketId: string): [string, Room] | undefined {
    const roomId = socketToRoom.get(socketId);
    if (!roomId) return undefined;
    const room = rooms.get(roomId);
    if (!room) return undefined;
    return [roomId, room];
}

// ─── Handler principal ────────────────────────────────────────────────────────

export function registerRaceHandlers(io: Server, socket: Socket): void {

    // ── room:create ──────────────────────────────────────────────────────────
    socket.on('room:create', (data: { player: Omit<RacePlayer, 'socketId'> }) => {
        try {
            const roomId = generateRoomId();
            const player: RacePlayer = {
                ...data.player,
                socketId: socket.id,
                isLocal: false,
                progress: 0,
            };
            const room: Room = {
                roomId,
                players: [player],
                spectators: [],
                status: 'waiting',
            };
            rooms.set(roomId, room);
            socketToRoom.set(socket.id, roomId);
            socket.join(roomId);

            socket.emit('room:joined', serializeRoom(room));
        } catch (err) {
            console.error('[race] room:create error', err);
            socket.emit('room:error', 'Impossible de créer la salle');
        }
    });

    // ── room:join ────────────────────────────────────────────────────────────
    socket.on('room:join', (data: { roomId: string; player: Omit<RacePlayer, 'socketId'> }) => {
        try {
            const room = rooms.get(data.roomId);
            if (!room) {
                socket.emit('room:error', 'Salle introuvable');
                return;
            }
            if (room.status !== 'waiting') {
                socket.emit('room:error', 'La course a déjà commencé');
                return;
            }
            if (room.players.length >= 2) {
                socket.emit('room:error', 'Salle pleine (max 2 joueurs)');
                return;
            }

            const player: RacePlayer = {
                ...data.player,
                socketId: socket.id,
                isLocal: false,
                progress: 0,
            };
            room.players.push(player);
            socketToRoom.set(socket.id, data.roomId);
            socket.join(data.roomId);

            socket.emit('room:joined', serializeRoom(room));
            socket.to(data.roomId).emit('room:updated', serializeRoom(room));
        } catch (err) {
            console.error('[race] room:join error', err);
            socket.emit('room:error', 'Impossible de rejoindre la salle');
        }
    });
    
    socket.on('room:leave', (data: { roomId: string }) => {
        const room = rooms.get(data.roomId);
        if (!room) return;
        room.players = room.players.filter(p => p.socketId !== socket.id);
        socketToRoom.delete(socket.id);
        socket.leave(data.roomId);
    
        // Si un joueur quitte pendant la course, le joueur restant gagne
        if (room.status === 'racing' && room.players.length === 1) {
            const winner = room.players[0];
            if (!winner) return;
            room.status = 'finished';
            io.to(data.roomId).emit('race:finished', {
                winner: winner.name,
                winnerId: winner.id,
            });
            setTimeout(() => {
                rooms.delete(data.roomId);
            }, 5000);
            return;
        }

        if (room.players.length === 0) {
            rooms.delete(data.roomId);
        } else {
            io.to(data.roomId).emit('room:updated', serializeRoom(room));
        }
    });
    // ── spectate:join ────────────────────────────────────────────────────────
    socket.on('spectate:join', (data: { roomId: string }) => {
        try {
            const room = rooms.get(data.roomId);
            if (!room) {
                socket.emit('room:error', 'Salle introuvable');
                return;
            }
            room.spectators.push(socket.id);
            socketToRoom.set(socket.id, data.roomId);
            socket.join(data.roomId);
            socket.emit('spectate:joined', {
                ...serializeRoom(room),
                isSpectator: true,
            });
        } catch (err) {
            console.error('[race] spectate:join error', err);
        }
    });

    // ── room:start ───────────────────────────────────────────────────────────
    socket.on('room:start', (data: { roomId: string }) => {
        try {
            const room = rooms.get(data.roomId);
            if (!room) return;
            if (room.status !== 'waiting') return;

            const isHost = room.players[0]?.socketId === socket.id;
            if (!isHost) {
                socket.emit('room:start:error', "Seul l'hôte peut lancer la course");
                return;
            }

            room.status = 'countdown';

            io.to(data.roomId).emit('room:updated', {
                ...serializeRoom(room),
                status: 'countdown',
                countdown: 3,
            });

            let count = 3;
            room.countdownTimer = setInterval(() => {
                count--;
                if (count > 0) {
                    io.to(data.roomId).emit('race:countdown', { countdown: count });
                } else {
                    clearInterval(room.countdownTimer);
                    room.status = 'racing';
                    room.players.forEach(p => { p.progress = 0; });
                    io.to(data.roomId).emit('room:updated', {
                        ...serializeRoom(room),
                        status: 'racing',
                    });
                }
            }, 1000);
        } catch (err) {
            console.error('[race] room:start error', err);
        }
    });

    // ── player:move ──────────────────────────────────────────────────────────
    socket.on('player:move', (data: { progress: number }) => {
        try {
            const entry = findRoomBySocket(socket.id);
            if (!entry) return;
            const [roomId, room] = entry;

            if (room.status !== 'racing') return;

            const player = room.players.find(p => p.socketId === socket.id);
            if (!player) return;

            const RACE_DISTANCE = 500;
            const newProgress = Math.min(RACE_DISTANCE, Math.max(0, data.progress));

            if (newProgress < player.progress) return;

            player.progress = newProgress;

            socket.to(roomId).emit('player:moved', {
                playerId: player.id,
                progress: player.progress,
            });

            if (player.progress >= RACE_DISTANCE && room.status === 'racing') {
                room.status = 'finished';
                io.to(roomId).emit('race:finished', {
                    winner: player.name,
                    winnerId: player.id,
                });
                setTimeout(() => {
                    rooms.delete(roomId);
                }, 5000);
            }
        } catch (err) {
            console.error('[race] player:move error', err);
        }
    });

    // ── disconnect ───────────────────────────────────────────────────────────
    socket.on('disconnect', () => {
        const entry = findRoomBySocket(socket.id);
        socketToRoom.delete(socket.id);
        if (!entry) return;
        const [roomId, room] = entry;

        room.spectators = room.spectators.filter(id => id !== socket.id);

        const wasPlayer = room.players.some(p => p.socketId === socket.id);
        if (wasPlayer) {
            room.players = room.players.filter(p => p.socketId !== socket.id);

            if (room.players.length === 0) {
                if (room.countdownTimer) clearInterval(room.countdownTimer);
                rooms.delete(roomId);
            } else {
                if (room.status === 'racing' || room.status === 'countdown') {
                    if (room.countdownTimer) clearInterval(room.countdownTimer);
                    room.status = 'waiting';
                }
                io.to(roomId).emit('room:updated', serializeRoom(room));
            }
        }
    });
}
