import { Response, NextFunction, Router } from 'express';
import { JwtRequest } from '../middleware/auth';
import { getDb } from '../../prisma/init';
import { PrismaClient } from '../../prisma/generated/prisma/client';
import { Server } from 'socket.io';

let prisma: PrismaClient;

export default function createPetsRouter(io: Server) {
	const router = Router();

	router.post('/', async (req: JwtRequest, res: Response, next: NextFunction) => {
		console.log('[INFO] POST /pets:');
		const userId: number = req.userId!;
		const { name, cat, color, background } = req.body;
		prisma = getDb(prisma);

		try {
			const userUpdate = await prisma.user.update({
				where: { id: userId },
				data: {
					catName: name,
					cat: cat,
					color: color,
					background: background,
				},
				omit: {
					password: true,
				},
			});

			console.log('[USER] ', userUpdate);

			res.status(200).json(userUpdate);
		} catch (err: any) {
			console.error('[ERROR] POST /pets: ', err.message);
			res.status(500).json({ error: 'Internal server error' });
		}
	});

	router.get('/', async (req: JwtRequest, res: Response, next: NextFunction) => {
		console.log('[INFO] GET /pets:');
		const userId: number = req.userId!;
		prisma = getDb(prisma);

		// Parse the query
		let targetId: number;
		const { q } = req.query;
		console.log('[QUERY] ', q);
		if (q) {
			if (Array.isArray(q) || typeof q !== 'string')
				return res.status(400).json({ error: 'Invalid query' });
			const numericId: number = parseInt(q, 10);
			if (isNaN(numericId))
				return res.status(400).json({ error: 'Invalid userId' });
			targetId = numericId;
		}
		else {
			targetId = userId;
		}


		try {
			const userPets = await prisma.user.findUnique({
				where: { id: targetId, },
				select: {
					catName: true,
					cat: true,
					color: true,
					background: true,
				}
			})
			if (!userPets)
				return res.status(400).json({ error: "User not found" });

			res.status(200).json(userPets);

		} catch (err: any) {
			console.error('[ERROR] GET /pets: ', err.message);
			res.status(500).json({ error: 'Internal server error' });
		}
	});

	router.get('/state', async (req: JwtRequest, res: Response, next: NextFunction) => {
		console.log("[INFO] GET /pets/state: ");
		const userId: number = req.userId!;
		prisma = getDb(prisma);

		// Parse the query
		let targetId: number;
		const { q } = req.query;
		console.log('[QUERY] ', q);
		if (q) {
			if (Array.isArray(q) || typeof q !== 'string')
				return res.status(400).json({ error: 'Invalid query' });
			const numericId: number = parseInt(q, 10);
			if (isNaN(numericId))
				return res.status(400).json({ error: 'Invalid userId' });
			targetId = numericId;
		}
		else {
			targetId = userId;
		}

		try {
			const userPetsState = await prisma.petState.findUnique({
				where: { userId: targetId },
			});

			res.status(200).json(userPetsState);

		} catch (err: any) {
			console.error('[ERROR] GET /pets/state: ', err.message);
			res.status(500).json({ error: 'Internal server error' });
		}
	});

	router.put('/state', async (req: JwtRequest, res: Response, next: NextFunction) => {
		console.log("[INFO] PUT /pets/state: ");
		const userId: number = req.userId!;
		prisma = getDb(prisma);

		const { name, hunger, happiness, cleanliness, energy, lastFed, lastPlayed,
			lastCleaned, lastSlept } = req.body;

		const petStateData = {
			name, hunger, happiness, cleanliness, energy, lastFed,
			lastPlayed, lastCleaned, lastSlept
		};


		try {
			const result = await prisma.petState.upsert({
				where: { userId: userId },
				create: { userId, ...petStateData },
				update: { ...petStateData },
			});

			res.status(200).json(result);
			io.to(`pet:${userId}`).emit(`pet:state:${userId}`, result);

		} catch (err: any) {
			console.error('[ERROR] PUT /pets/state: ', err.message);
			res.status(500).json({ error: 'Internal server error' });
		}
	});

	return router;
}