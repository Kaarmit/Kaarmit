#!/bin/sh
set -eu

fatal() { echo "mariadb: $*" >&2; exit 1; }

read_secret() {
  var="$1"
  var_file="$2"
  eval val="\${$var:-}"
  eval file="\${$var_file:-}"
  if [ -n "$val" ] && [ -n "$file" ]; then fatal "$var and $var_file both set"; fi
  if [ -n "$file" ]; then [ -r "$file" ] || fatal "cannot read $file"; val="$(cat "$file")"; fi
  eval "$var=\$val"
  export "$var"
}

wait_mysql() {
  i=0
  while [ $i -lt 60 ]; do
    mysqladmin --protocol=socket --socket=/run/mysqld/mysqld.sock ping >/dev/null 2>&1 && return 0
    i=$((i + 1))
    sleep 1
  done
  return 1
}

: "${MYSQL_DATABASE:?missing MYSQL_DATABASE}"
: "${MYSQL_USER:?missing MYSQL_USER}"
read_secret MYSQL_PASSWORD MYSQL_PASSWORD_FILE
read_secret MYSQL_ROOT_PASSWORD MYSQL_ROOT_PASSWORD_FILE
[ -n "${MYSQL_PASSWORD:-}" ] || fatal "missing MYSQL_PASSWORD or MYSQL_PASSWORD_FILE"
[ -n "${MYSQL_ROOT_PASSWORD:-}" ] || fatal "missing MYSQL_ROOT_PASSWORD or MYSQL_ROOT_PASSWORD_FILE"

mkdir -p /run/mysqld /var/lib/mysql
chown -R mysql:mysql /run/mysqld /var/lib/mysql

BOOT_OK="/var/lib/mysql/.inception_bootstrapped"

if [ ! -d /var/lib/mysql/mysql ]; then
  echo "mariadb: initializing datadir"
  mariadb-install-db --user=mysql --datadir=/var/lib/mysql >/dev/null
fi

if [ ! -f "$BOOT_OK" ]; then
  echo "mariadb: bootstrap -> create db/user/grants"

  mysqld --user=mysql --datadir=/var/lib/mysql \
    --socket=/run/mysqld/mysqld.sock \
    --pid-file=/run/mysqld/mysqld.pid \
    --skip-networking --bind-address=127.0.0.1 \
    >/dev/null 2>&1 &

  wait_mysql || fatal "bootstrap mysqld not ready"

  mysql --protocol=socket --socket=/run/mysqld/mysqld.sock -uroot <<SQL
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;

CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
SQL

  mysql --protocol=socket --socket=/run/mysqld/mysqld.sock -uroot -p"${MYSQL_ROOT_PASSWORD}" -e \
    "SELECT 1 FROM mysql.user WHERE User='${MYSQL_USER}' AND Host='%' LIMIT 1;" \
    | grep -q 1 || fatal "bootstrap verification failed: user not created"

  touch "$BOOT_OK"
  chown mysql:mysql "$BOOT_OK"

  mysqladmin --protocol=socket --socket=/run/mysqld/mysqld.sock -uroot -p"${MYSQL_ROOT_PASSWORD}" shutdown
  echo "mariadb: bootstrap done"
else
  echo "mariadb: bootstrap marker exists -> skip"
fi

exec mysqld --user=mysql --datadir=/var/lib/mysql \
  --socket=/run/mysqld/mysqld.sock \
  --pid-file=/run/mysqld/mysqld.pid \
  --bind-address=0.0.0.0
