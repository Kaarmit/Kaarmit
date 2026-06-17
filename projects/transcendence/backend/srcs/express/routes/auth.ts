import { Request, Response, NextFunction, Router } from 'express';
//import { AuthResponse, AuthUser } from '../types/auth';
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import speakeasy from 'speakeasy';
import QRCode from 'qrcode';
import { getDb } from '../../prisma/init';
import { PrismaClient } from '../../prisma/generated/prisma/client';

let prisma: PrismaClient;
const router = Router();

router.post('/register', async (req: Request, res: Response, next: NextFunction) => {
	console.log("[INFO] Register:");
	console.log(req.body);

	const { email, username, password, cat, color, background, avatarUrl } = req.body;

	prisma = getDb(prisma);

	if (!username || !password)
		return res.status(400).json({ error: "Missing fieds" });

	const PASSWORD_MIN = 8;
	const PASSWORD_MAX = 30;
	const passwordRegex = /^(?=.*\d)(?=.*[@$!%*?&.])[A-Za-z\d@$!%*?&.]{8,}$/;

	if (password.length < PASSWORD_MIN)
		return res.status(400).json({
			error: `Password must be at least ${PASSWORD_MIN} characters long.`
		});

	if (password.length > PASSWORD_MAX)
		return res.status(400).json({
			error: `Password must not exceed ${PASSWORD_MAX} characters.`
		});

	if (!passwordRegex.test(password))
		return res.status(400).json({
			error: 'Password must include a number and a special character.'
		});


	try {
		// Check if user already exists
		const mailExist = await prisma.user.findUnique({
			where: { email: email },
			select: { id: true }
		});

		if (mailExist) {
			return res.status(409).json({ error: "Email already taken" });
		}

		const userExist = await prisma.user.findUnique({
			where: { username: username },
			select: { id: true }
		});

		if (userExist) {
			return res.status(409).json({ error: "Username already taken" });
		}

		// Hash password with bcrypt
		const hashedPassword = await bcrypt.hash(
			password,
			parseInt(process.env.BCRYPT_ROUNDS ?? '12', 10)
		);

		// Create new user
		const newUser = await prisma.user.create({
			data: {
				username: username,
				email: email,
				password: hashedPassword,
				avatarUrl: avatarUrl ?? null,
				cat: cat,
				color: color,
				background: background,
			},
			omit: {
				password: true,
			},
		});

		console.log("[INFO] Prisma:");
		console.log(newUser);

		// Generate token with jwt
		const token = jwt.sign(
			{ userId: newUser.id },
			process.env.JWT_SECRET!,
			{ expiresIn: '7d' }
		);

		// Populate the response with the data that the frontend will need
		res.status(201).json({
			user: {
				id: newUser.id,
				username: newUser.username,
				email: newUser.email,
				avatarUrl: newUser.avatarUrl,
				customizations: {
					cat: newUser.cat,
					color: newUser.color,
					background: newUser.background,
				},
			},
			token,
		});

	} catch (err: any) {
		if (err.code === 'P2002') {
			const field = (err.meta?.target as string[])?.includes('email')
				? 'Email'
				: 'Username';

			return res.status(409).json({
				error: `${field} already taken`
			});
		}

		console.error('[ERROR] /register: ', err.message);

		res.status(500).json({
			error: 'Internal server error'
		});
	}
});

router.post('/login', async (req: Request, res: Response, next: NextFunction) => {
	console.log("[INFO] login:");
	console.log(req.body);

	const { password } = req.body;
	const identifier = req.body.email ?? req.body.username;

	prisma = getDb(prisma);

	try {
		// Check if email or username is not in the database
		const user = await prisma.user.findFirst({
			where: {
				OR: [
					{ email: identifier },
					{ username: identifier },
				]
			}
		});

		if (!user) {
			return res.status(401).json({
				error: 'Invalid credentials'
			});
		}

		console.log("[INFO] Prisma:");
		console.log(user);

		// Check password match
		const isValid = await bcrypt.compare(password, user.password);

		if (!isValid) {
			return res.status(401).json({
				error: 'Invalid credentials'
			});
		}

		console.log("[INFO] Password valid;");

		// If 2FA is enabled, do NOT send final auth token yet
		if (user.twoFactorEnabled) {
			const tempToken = jwt.sign(
				{
					userId: user.id,
					pending2FA: true
				},
				process.env.JWT_SECRET!,
				{ expiresIn: '5m' }
			);

			return res.status(200).json({
				requires2FA: true,
				tempToken: tempToken,
			});
		}

		// Generate normal token
		const token = jwt.sign(
			{ userId: user.id },
			process.env.JWT_SECRET!,
			{ expiresIn: '7d' }
		);

		res.status(200).json({
			user: {
				id: user.id,
				username: user.username,
				email: user.email,
				avatarUrl: user.avatarUrl,
				customizations: {
					cat: user.cat,
					color: user.color,
					background: user.background,
				},
			},
			token: token,
		});

	} catch (err: any) {
		console.error('[ERROR] /login: ', err.message);

		return res.status(500).json({
			error: 'Internal server error'
		});
	}
});

router.post('/2fa/setup', async (req: Request, res: Response) => {
	const { userId } = req.body;

	prisma = getDb(prisma);

	if (!userId) {
		return res.status(400).json({
			error: 'Missing userId'
		});
	}

	try {
		const user = await prisma.user.findUnique({
			where: { id: userId },
		});

		if (!user) {
			return res.status(404).json({
				error: 'User not found'
			});
		}

		const secret = speakeasy.generateSecret({
			name: `Nekotchi:${user.email}`,
		});

		await prisma.user.update({
			where: { id: user.id },
			data: {
				twoFactorSecret: secret.base32,
				twoFactorEnabled: false,
			},
		});

		const qrCodeUrl = await QRCode.toDataURL(
			secret.otpauth_url!
		);

		return res.status(200).json({
			qrCodeUrl,
		});

	} catch (err: any) {
		console.error('[ERROR] /2fa/setup: ', err.message);

		return res.status(500).json({
			error: 'Internal server error'
		});
	}
});

router.post('/2fa/confirm', async (req: Request, res: Response) => {
	const { userId, code } = req.body;

	prisma = getDb(prisma);

	if (!userId || !code) {
		return res.status(400).json({
			error: 'Missing userId or code'
		});
	}

	try {
		const user = await prisma.user.findUnique({
			where: { id: userId },
		});

		if (!user || !user.twoFactorSecret) {
			return res.status(404).json({
				error: '2FA setup not found'
			});
		}

		const isValid = speakeasy.totp.verify({
			secret: user.twoFactorSecret,
			encoding: 'base32',
			token: code,
			window: 1,
		});

		if (!isValid) {
			return res.status(401).json({
				error: 'Invalid 2FA code'
			});
		}

		await prisma.user.update({
			where: { id: user.id },
			data: {
				twoFactorEnabled: true,
				twoFactorConfirmedAt: new Date(),
			},
		});

		return res.status(200).json({
			message: '2FA enabled successfully'
		});

	} catch (err: any) {
		console.error('[ERROR] /2fa/confirm: ', err.message);

		return res.status(500).json({
			error: 'Internal server error'
		});
	}
});

router.post('/2fa/verify-login', async (req: Request, res: Response) => {
	const { tempToken, code } = req.body;

	prisma = getDb(prisma);

	if (!tempToken || !code) {
		return res.status(400).json({
			error: 'Missing tempToken or code'
		});
	}

	try {
		const decoded = jwt.verify(
			tempToken,
			process.env.JWT_SECRET!
		) as { userId: number; pending2FA?: boolean };

		if (!decoded.pending2FA) {
			return res.status(401).json({
				error: 'Invalid temporary token'
			});
		}

		const user = await prisma.user.findUnique({
			where: { id: decoded.userId },
		});

		if (!user || !user.twoFactorSecret || !user.twoFactorEnabled) {
			return res.status(401).json({
				error: '2FA not enabled'
			});
		}

		const isValid = speakeasy.totp.verify({
			secret: user.twoFactorSecret,
			encoding: 'base32',
			token: code,
			window: 1,
		});

		if (!isValid) {
			return res.status(401).json({
				error: 'Invalid 2FA code'
			});
		}

		const token = jwt.sign(
			{ userId: user.id },
			process.env.JWT_SECRET!,
			{ expiresIn: '7d' }
		);

		return res.status(200).json({
			user: {
				id: user.id,
				username: user.username,
				email: user.email,
				avatarUrl: user.avatarUrl,
				customizations: {
					cat: user.cat,
					color: user.color,
					background: user.background,
				},
			},
			token: token,
		});

	} catch (err: any) {
		console.error('[ERROR] /2fa/verify-login: ', err.message);

		return res.status(401).json({
			error: 'Invalid or expired temporary token'
		});
	}
});

export default router;