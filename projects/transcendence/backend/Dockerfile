FROM node:20-alpine

WORKDIR /app

COPY package*.json ./
COPY srcs/prisma/schema.prisma ./srcs/prisma/schema.prisma

RUN npm install
RUN npx prisma generate --schema=srcs/prisma/schema.prisma

RUN apk add --no-cache openssl && \
	openssl req -x509 -newkey rsa:4096 \
	-keyout /app/key.pem -out /app/cert.pem \
	-days 365 -nodes -subj "/CN=localhost"

COPY . .

EXPOSE 3000

ENTRYPOINT ["sh", "/app/entrypoint.sh"]