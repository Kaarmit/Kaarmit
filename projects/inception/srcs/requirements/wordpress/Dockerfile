FROM debian:bullseye

RUN apt-get update && apt-get install -y --no-install-recommends \
    php7.4 php7.4-fpm php7.4-mysql php7.4-curl php7.4-gd php7.4-mbstring php7.4-xml php7.4-zip \
    mariadb-client curl ca-certificates tar \
 && rm -rf /var/lib/apt/lists/*

# wp-cli
RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    -o /usr/local/bin/wp \
 && chmod +x /usr/local/bin/wp

# PHP-FPM pool config
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# entrypoint
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh \
 && mkdir -p /run/php /var/www/html \
 && chown -R www-data:www-data /run/php /var/www/html

WORKDIR /var/www/html

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["php-fpm7.4", "-F"]