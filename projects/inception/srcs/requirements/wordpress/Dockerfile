FROM debian:bookworm

RUN apt-get update && apt-get install -y --no-install-recommends \
    php8.2 php8.2-fpm php8.2-mysql php8.2-curl php8.2-gd php8.2-mbstring php8.2-xml php8.2-zip \
    mariadb-client curl ca-certificates tar \
 && rm -rf /var/lib/apt/lists/*

# wp-cli
RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    -o /usr/local/bin/wp \
 && chmod +x /usr/local/bin/wp

# PHP-FPM pool config
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

# entrypoint
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh \
 && mkdir -p /run/php /var/www/html \
 && chown -R www-data:www-data /run/php /var/www/html

WORKDIR /var/www/html

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["php-fpm8.2", "-F"]