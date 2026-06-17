import { Request, Response, NextFunction, Router } from 'express';
import { JwtRequest } from '../middleware/auth';
import bcrypt from 'bcrypt';
import { getDb } from '../../prisma/init';
import { PrismaClient } from '../../prisma/generated/prisma/client';

let prisma: PrismaClient;
const router = Router();

router.get('/me', async (req: JwtRequest, res: Response, next: NextFunction) => {
	const userId: number = req.userId!;
	prisma = getDb(prisma);

	try {
		const user = await prisma.user.findUnique({
			where: { id: userId },
			select: {
				id: true,
				username: true,
				email: true,
				avatarUrl: true,
				catName: true,
				cat: true,
				color: true,
				background: true,
			},
		});

		if (!user) {
			return res.status(404).json({ error: 'User not found' });
		}

		return res.status(200).json({
			user: {
				id: user.id,
				username: user.username,
				email: user.email,
				avatarUrl: user.avatarUrl,
				catName: user.catName,
				customizations: {
					cat: user.cat,
					color: user.color,
					background: user.background,
				},
			},
		});
	} catch (err: any) {
		console.error('[ERROR] GET /users/me: ', err.message);
		return res.status(500).json({ error: 'Internal server error' });
	}
});

router.get('/search', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] /users/search:');
	const userId: number = req.userId!;
	prisma = getDb(prisma);

	// Parse the query
	const { q } = req.query;
	console.log('[QUERY] ', q);
	if (!q || Array.isArray(q) || typeof q !== 'string')
		return res.status(400).json({ error: 'Invalid search query' });

	try {
		const users = await prisma.user.findMany({
			where: {
				username: {
					contains: q,
					mode: 'insensitive',
				},
				NOT: {
					id: userId,
				},
			},
			omit: { password: true, },
		});

		console.log('[USERS FOUND] ', users);
		
		res.status(200).json(users);

	} catch (err: any) {
		console.error('[ERROR] GET /users/search: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

router.put('/profile', async (req: JwtRequest, res: Response, next: NextFunction) => {
	console.log('[INFO] /users/profile:');
	const userId: number = req.userId!;
	const { newPassword, newUsername, newAvatarUrl } = req.body;
	prisma = getDb(prisma);

	if (!newPassword && !newUsername && !newAvatarUrl)
		return res.status(400).json({ error: "At least one of `newUsername' or `newPassword' or `newAvatarUrl` must be present" });

	try {
		const data: Partial<{ username: string, password: string, avatarUrl: string }> = {};
		if (newUsername) data.username = newUsername;
		if (newPassword) data.password = await bcrypt.hash(newPassword, parseInt(process.env.BCRYPT_ROUNDS ?? '12', 10));
		if (newAvatarUrl) data.avatarUrl = newAvatarUrl;

		const updatedUser = await prisma.user.update({
			where: { id: userId },
			data,
			omit: { password: true },
		});

		res.status(200).json(updatedUser);

	} catch (err: any) {
		if (err.code === 'P2002')
			return res.status(409).json({ error: "Username already taken" });
		console.error('[ERROR] PUT /users/profile: ', err.message);
		res.status(500).json({ error: 'Internal server error' });
	}
});

export default router;