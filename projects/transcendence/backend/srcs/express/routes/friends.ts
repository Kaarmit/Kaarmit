import { Request, Response, NextFunction, Router } from 'express';
import { JwtRequest } from '../middleware/auth';
import { getDb, getUserFriends} from '../../prisma/init';
import { PrismaClient } from '../../prisma/generated/prisma/client';
import { onlineUsers } from '../app/socket'
import { io } from '../app/server'

let prisma: PrismaClient;
const router = Router();

router.get('/', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] Friends:');
	const userId: number = req.userId!;
	prisma = getDb(prisma);

	try {
		const friends = await getUserFriends(prisma, userId);
		if (!friends)
			return res.status(400).json({ error: "User not found"});

		console.log('[FRIENDS] ', friends);
		
		res.status(200).json(friends);

	} catch (err: any) {
		console.error('[ERROR] /friends: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

router.post('/requests', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] POST SendRequest:');
	const fromUserId: number = req.userId!;
	const { userId: toUserId } = req.body;
	prisma = getDb(prisma);

	try {
		if (fromUserId === toUserId)
			return res.status(409).json({ error: "Cannot send friend request to yourself"});

		const newFriendUser = await prisma.user.findUnique({
			where: { id: toUserId },
			select: { id: true },
		});
		if (!newFriendUser)
			return res.status(400).json({ error: "Friend user does not exist"});

		const alreadyFriend = await prisma.friendRequest.findFirst({
			where: {
				OR: [
					{ fromUserId: fromUserId, toUserId: toUserId },
					{ fromUserId: toUserId, toUserId: fromUserId },
				],
				status: 'ACCEPTED',
			},
			select: {
				id: true,
			},
		});
		if (alreadyFriend)
			return res.status(409).json({ error: 'Already friends' });

		const upserted = await prisma.friendRequest.upsert({
			where: {
				fromUserId_toUserId: { fromUserId, toUserId },
			},
			include: {
				fromUser: { select: { id: true, username: true, avatarUrl: true } },
				toUser: { select: { id: true, username: true, avatarUrl: true } },
			},
			create: {
				fromUserId: fromUserId,
				toUserId:	toUserId,
				status:		"PENDING",
			},
			update: {
				status: "PENDING",
			},
		});

		console.log('[NEW FRIEND] ', upserted);

		// Notify the recipient in real-time if they're online
		const toSocketId = onlineUsers.get(toUserId);
		if (toSocketId && upserted) {
			io.to(toSocketId).emit('friend:request', { request: upserted });
		}

		res.status(201).json(upserted);

	} catch (err: any) {
		console.error('[ERROR] POST /friends/requests: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

router.get('/requests', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] GET SendRequest:');
	const userId: number = req.userId!;
	prisma = getDb(prisma);

	try {
		const user = await prisma.user.findUnique({
			where: { id: userId },
			include: {
				sentRequests: {
					include: { fromUser: { select: { id: true, username: true, avatarUrl: true } }, toUser: { select: { id: true, username: true, avatarUrl: true } } },
				},
				receivedRequests: {
					include: { fromUser: { select: { id: true, username: true, avatarUrl: true } }, toUser: { select: { id: true, username: true, avatarUrl: true } } },
				},
			},
		});
		if (!user)
			return res.status(400).json({ error: 'User not found' });

		const requests = [
			...user.sentRequests,
			...user.receivedRequests,
		];

		console.log('[REQUESTS] ', requests);
		
		res.status(200).json({ 
			requests: requests,
		});

	} catch (err: any) {
		console.error('[ERROR] GET /friends/requests: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

router.put('/requests/:id', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] PUT Request:');
	const userId: number = req.userId!;
	const { status } = req.body;
	prisma = getDb(prisma);
	console.log(req.params);

	// Parse the id
	if (!req.params.id || Array.isArray(req.params.id))
		return res.status(400).json({ error: 'Invalid request id' });
	const requestId: number = parseInt(req.params.id, 10);
	if (isNaN(requestId))
		return res.status(400).json({ error: 'Invalid request id' });

	const upperStatus = status.toUpperCase();

	try {
		const request = await prisma.friendRequest.update({
			where: {
				id:			requestId,
				toUserId:	userId, // authenticated user is the receiver
			},
			data: {
				status: upperStatus,
			},
			include: {
				fromUser: { omit: { password: true } },
				toUser: { omit: { password: true } },
			},
		});

		console.log('[UPDATED] ', request);
		if (upperStatus === 'ACCEPTED') {
			const fromSocketId = onlineUsers.get(request.fromUserId);
			const toSocketId = onlineUsers.get(request.toUserId);

			if (fromSocketId)
				io.to(fromSocketId).emit('friend:added', { friend: request.toUser });
			if (toSocketId)
				io.to(toSocketId).emit('friend:added', { friend: request.fromUser });
		} else if (upperStatus === 'REFUSED') {
			// Notify the original sender that their friend request was refused
			const fromSocketId = onlineUsers.get(request.fromUserId);
			if (fromSocketId) {
				io.to(fromSocketId).emit('friend:request:refused', { request });
			}
		}

		res.status(200).json(request);

	} catch (err: any) {
		console.error('[ERROR] PUT /requests/:requestId: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

router.delete('/:id', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] DELETE Friends:');
	const userId: number = req.userId!;
	prisma = getDb(prisma);

	// Parse the id
	if (!req.params.id || Array.isArray(req.params.id))
		return res.status(400).json({ error: 'Invalid friend id' });
	const friendId: number = parseInt(req.params.id, 10);
	if (isNaN(friendId))
		return res.status(400).json({ error: 'Invalid friend id' });

	try {
		const friendRequest = await prisma.friendRequest.findFirst({
			where: {
				OR: [
					{ fromUserId: userId, toUserId: friendId },
					{ fromUserId: friendId, toUserId: userId },
				],
				status: 'ACCEPTED',
			},
			select: {
				id: true,
			},
		});
		if (!friendRequest)
			return res.status(404).json({ error: 'Friendship not found' });

		await prisma.friendRequest.delete({
			where: { id: friendRequest.id, },
		});

		const deletedSocketId = onlineUsers.get(friendId);
		if (deletedSocketId)
			io.to(deletedSocketId).emit('friend:removed', { friendId: userId });

		res.status(204).send();

	} catch (err: any) {
		console.error('[ERROR] DELETE /:friendId: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

export default router;