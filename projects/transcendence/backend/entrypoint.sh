#!/bin/sh
set -e

echo "[ENTRYPOINT] Migration Prisma..."
npx prisma migrate deploy --schema=srcs/prisma/schema.prisma

echo "[ENTRYPOINT] Starting server..."
exec npm run dev