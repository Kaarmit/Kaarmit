#!/bin/sh
set -eu

fatal() { echo "wordpress: $*" >&2; exit 1; }

read_secret() {
  var="$1"; var_file="$2"
  eval val="\${$var:-}"
  eval file="\${$var_file:-}"
  if [ -n "$val" ] && [ -n "$file" ]; then fatal "$var and $var_file are both set"; fi
  if [ -n "$file" ]; then [ -r "$file" ] || fatal "cannot read $file"; val="$(cat "$file")"; fi
  eval "$var=\$val"; export "$var"
}

: "${MYSQL_DATABASE:?missing MYSQL_DATABASE}"
: "${MYSQL_USER:?missing MYSQL_USER}"
read_secret MYSQL_PASSWORD MYSQL_PASSWORD_FILE
[ -n "${MYSQL_PASSWORD:-}" ] || fatal "missing MYSQL_PASSWORD or MYSQL_PASSWORD_FILE"

: "${DOMAIN_NAME:?missing DOMAIN_NAME}"

: "${WP_ADMIN_USER:?missing WP_ADMIN_USER}"
: "${WP_ADMIN_EMAIL:?missing WP_ADMIN_EMAIL}"
read_secret WP_ADMIN_PASSWORD WP_ADMIN_PASSWORD_FILE
[ -n "${WP_ADMIN_PASSWORD:-}" ] || fatal "missing WP_ADMIN_PASSWORD or WP_ADMIN_PASSWORD_FILE"

: "${WP_USER:?missing WP_USER}"
: "${WP_USER_EMAIL:?missing WP_USER_EMAIL}"
read_secret WP_USER_PASSWORD WP_USER_PASSWORD_FILE
[ -n "${WP_USER_PASSWORD:-}" ] || fatal "missing WP_USER_PASSWORD or WP_USER_PASSWORD_FILE"

DB_HOST="${DB_HOST:-mariadb}"
WP_PATH="/var/www/html"
WP_URL="https://${DOMAIN_NAME}"
MARK="${WP_PATH}/.inception_wp_installed"

i=0
while [ $i -lt 60 ]; do
  mysql --connect-timeout=2 -h "$DB_HOST" -u "$MYSQL_USER" -p"$MYSQL_PASSWORD" "$MYSQL_DATABASE" \
    -e "SELECT 1;" >/dev/null 2>&1 && break
  i=$((i+1)); sleep 1
done
[ $i -lt 60 ] || fatal "db not ready for app user"

mkdir -p /var/www/.wp-cli/cache
chown -R www-data:www-data /var/www/.wp-cli

if [ ! -f "${WP_PATH}/wp-settings.php" ]; then
  echo "wordpress: downloading core"
  chown -R www-data:www-data "${WP_PATH}"
  su -s /bin/sh -c "wp core download --path='${WP_PATH}' --allow-root" www-data
fi

if [ ! -f "${WP_PATH}/wp-config.php" ]; then
  echo "wordpress: generating wp-config.php"
  su -s /bin/sh -c "wp config create \
    --path='${WP_PATH}' \
    --dbname='${MYSQL_DATABASE}' \
    --dbuser='${MYSQL_USER}' \
    --dbpass='${MYSQL_PASSWORD}' \
    --dbhost='${DB_HOST}' \
    --skip-check \
    --allow-root" www-data
fi

if [ ! -f "$MARK" ]; then
  echo "wordpress: installing"
  su -s /bin/sh -c "wp core install \
    --path='${WP_PATH}' \
    --url='${WP_URL}' \
    --title='Inception' \
    --admin_user='${WP_ADMIN_USER}' \
    --admin_password='${WP_ADMIN_PASSWORD}' \
    --admin_email='${WP_ADMIN_EMAIL}' \
    --skip-email \
    --allow-root" www-data

  su -s /bin/sh -c "wp user get '${WP_USER}' --path='${WP_PATH}' --allow-root >/dev/null 2>&1 || \
    wp user create '${WP_USER}' '${WP_USER_EMAIL}' \
      --user_pass='${WP_USER_PASSWORD}' \
      --role='author' \
      --path='${WP_PATH}' \
      --allow-root" www-data

  touch "$MARK"
  chown www-data:www-data "$MARK"
  echo "wordpress: install done"
else
  echo "wordpress: marker exists -> skip install"
fi

exec "$@"