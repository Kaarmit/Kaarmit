# Stage 1 : build
FROM node:20-alpine AS builder

WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

# Stage 2 : serve
FROM nginx:alpine
RUN apk add --no-cache openssl && \
	openssl req -x509 -newkey rsa:4096 \
	-keyout /etc/nginx/key.pem -out /etc/nginx/cert.pem \
	-days 365 -nodes -subj "/CN=localhost"
COPY --from=builder /app/dist /usr/share/nginx/html
COPY nginx.conf /etc/nginx/conf.d/default.conf                                
EXPOSE 443                                 