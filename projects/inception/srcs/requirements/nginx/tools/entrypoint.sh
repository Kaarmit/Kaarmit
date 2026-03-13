#!/bin/sh
set -eu

CRT="/etc/nginx/ssl/nginx.crt"
KEY="/etc/nginx/ssl/nginx.key"

mkdir -p /etc/nginx/ssl /run/nginx

if [ ! -f "$CRT" ] || [ ! -f "$KEY" ]; then
    openssl req -x509 -nodes -days 365 \
        -newkey rsa:2048 \
        -keyout "$KEY" \
        -out "$CRT" \
        -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=Inception/CN=aarmitan.42.fr"
fi

nginx -t
exec "$@"
