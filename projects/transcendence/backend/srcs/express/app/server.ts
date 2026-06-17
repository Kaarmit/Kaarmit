import 'dotenv/config'
import express, { Request, Response, NextFunction } from "express";
import cors from "cors";
import https from "https";
import fs from "fs";
import { Server, Socket } from "socket.io";
import jwt from "jsonwebtoken";
import { PrismaClient } from '../../prisma/generated/prisma/client';
import { initSocket } from './socket';
import { authenticate } from '../middleware/auth';

// Routes
import auth from "../routes/auth";
import conversations from '../routes/conversations';
import friends from "../routes/friends";
import users from "../routes/users";
import createPetsRouter from "../routes/pets";

const app = express();
const prisma = new PrismaClient();
const PORT = process.env.PORT || 3000;
const httpServer = https.createServer({
	key: fs.readFileSync('key.pem'),
	cert: fs.readFileSync('cert.pem'),
}, app);

const corsOrigin = (origin: string | undefined, callback: (err: Error | null, allow?: boolean) => void) => {
  const allowedOrigins = [
    'https://localhost:8443',  // Production
    'http://localhost:5173',   // Frontend dev
  ];
  if (!origin || allowedOrigins.includes(origin)) {
    callback(null, true);
  } else {
    callback(new Error('CORS policy violation'));
  }
};

const io = new Server(httpServer, {
  cors: { origin: corsOrigin, credentials: true }
});

initSocket(io);

// ── Middlewares Express ───────────────────────────────────────────────────────
app.use(express.json({ limit: '5mb' }));
app.use(cors({ origin: corsOrigin, credentials: true }));

// ── Routes ────────────────────────────────────────────────────────────────────
app.use('/auth', auth);
app.use('/conversations', conversations);
app.use('/pets', authenticate, createPetsRouter(io));
app.use('/friends', authenticate, friends);
app.use('/users', authenticate, users);

// ── Error handler ─────────────────────────────────────────────────────────────
app.use((err: Error, req: Request, res: Response, next: NextFunction) => {
  console.error(err.stack);
  res.status(500).json({ error: err.message });
});

// ── Démarrage ─────────────────────────────────────────────────────────────────
async function start(): Promise<void> {
  httpServer.listen(PORT, () => console.log(`[INFO] Server running on https://localhost:${PORT}`));
}

start().catch(err => {
  console.error('[FATAL]', err);
  process.exit(1);
});

export { io };
export default app;