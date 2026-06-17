import { Server, Socket } from 'socket.io';

export function registerPetHandlers(io: Server, socket: Socket) {
	socket.on('pet:subscribe', (payload: { userId: number }) => {
		socket.join(`pet:${payload.userId}`);
	});

	socket.on('pet:unsubscribe', (payload: { userId: number }) => {
		socket.leave(`pet:${payload.userId}`);
	});

	socket.on('pet:state:update', (payload: { userId: number; petState: any }) => {
		if (!payload?.userId || !payload?.petState) return;
		io.to(`pet:${payload.userId}`).emit(`pet:state:${payload.userId}`,
			payload.petState);
	});

}