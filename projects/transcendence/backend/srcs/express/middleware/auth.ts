import { Request, Response, NextFunction } from 'express';
import jwt from 'jsonwebtoken';

export interface JwtRequest extends Request {
	userId?: number;
}

export const authenticate = (req: JwtRequest, res: Response, next: NextFunction) => {
	const authHeader = req.headers.authorization;
	if (!authHeader?.startsWith('Bearer '))
		return res.status(401).json({ error: 'Not authenticated' });

	const token = authHeader.split(' ')[1];
	if (!token) throw new Error();
	try {
		const payload = jwt.verify(token!, process.env.JWT_SECRET!) as unknown as { userId: number };
		req.userId = payload.userId;
		next();
	} catch {
		res.status(401).json({ error: 'Invalid or expired token' });
	}
};