#!/bin/sh
set -eu

: "${DOMAIN_NAME:?missing DOMAIN_NAME}"

CRT="/etc/nginx/ssl/nginx.crt"
KEY="/etc/nginx/ssl/nginx.key"

# cert idempotent
if [ ! -f "$CRT" ] || [ ! -f "$KEY" ]; then
  openssl req -x509 -nodes -days 365 \
    -newkey rsa:2048 \
    -keyout "$KEY" \
    -out "$CRT" \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=Inception/CN=${DOMAIN_NAME}"
fi

# render nginx conf from template
sed "s/__DOMAIN_NAME__/${DOMAIN_NAME}/g" \
  /etc/nginx/templates/default.conf.template \
  > /etc/nginx/conf.d/default.conf

exec "$@"
