import { PrismaClient } from './generated/prisma/client';
import { PrismaPg } from '@prisma/adapter-pg';

export function getDb(prisma: PrismaClient): PrismaClient {
	if (!prisma) {
		prisma = new PrismaClient({
			adapter: new PrismaPg({ connectionString: process.env.DATABASE_URL! }),
		});
	}
	return prisma;
}

export async function getUserFriends(prisma: PrismaClient, userId: number) {
	const user = await prisma.user.findUnique({
		where: { id: userId },
		include: {
			sentRequests: {
				where: { status: "ACCEPTED" },
				include: {
					toUser: {
						omit: {
							password: true,
						},
					},
				},
			},
			receivedRequests: {
				where: { status: "ACCEPTED" },
				include: {
					fromUser: {
						omit: {
							password: true,
						},
					},
				},
			},
		},
	});
	if (!user)
		return [];

	return [
		...user.sentRequests.map((r: any) => r.toUser),
		...user.receivedRequests.map((r: any) => r.fromUser),
	];
}