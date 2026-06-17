import { Router, Request, Response } from 'express';
import { PrismaClient } from '../../prisma/generated/prisma/client';
import { authenticate } from '../middleware/auth';
import { JwtRequest } from '../middleware/auth';

const router = Router();
const prisma = new PrismaClient();

router.post('/', authenticate, async (req: JwtRequest, res: Response) => {
  const userId = req.userId!;
  const { friendId } = req.body;

  if (!friendId || typeof friendId !== 'number') {
    return res.status(400).json({ error: 'friendId invalide' });
  }

  const friend = await prisma.user.findUnique({ where: { id: friendId } });
  if (!friend) {
    return res.status(404).json({ error: 'Utilisateur introuvable' });
  }

  const existing = await prisma.conversation.findFirst({
    where: {
      AND: [
        { participants: { some: { userId } } },
        { participants: { some: { userId: friendId } } },
      ]
    },
    include: { participants: true }
  });

  if (existing && existing.participants.length === 2) {
    return res.json(existing);
  }

  const conversation = await prisma.$transaction(async (tx: any) => {
    return tx.conversation.create({
      data: {
        participants: {
          create: [{ userId }, { userId: friendId }]
        }
      },
      include: { participants: true }
    });
  });

  res.status(201).json(conversation);
});

router.get('/:id/messages', authenticate, async (req: JwtRequest, res: Response) => {
  const conversationId = parseInt(req.params.id as string);
  const userId = req.userId!;
  const { cursor } = req.query;

  const participant = await prisma.conversationParticipant.findUnique({
    where: { userId_conversationId: { userId, conversationId } }
  });
  if (!participant) return res.status(403).json({ error: 'Accès refusé' });

  const messages = await prisma.message.findMany({
    where: { conversationId },
    include: { sender: { select: { id: true, username: true } } },
    orderBy: { createdAt: 'desc' },
    take: 50,
    ...(cursor && {
      skip: 1,
      cursor: { id: parseInt(cursor as string) }
    })
  });

  res.json(messages.reverse());
});

export default router;