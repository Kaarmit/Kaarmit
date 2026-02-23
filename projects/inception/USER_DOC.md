# User Documentation

## Overview

This infrastructure provides:

- A secure HTTPS website
- A WordPress application
- A MariaDB database backend

Only port 443 is exposed to the host.

---

## Starting the Project

Build and launch:

make  
make up

Verify containers:

docker compose ps

---

## Stopping the Project

Stop containers:

make down

Remove volumes (warning: deletes all persistent data):

docker compose down -v

---

## Accessing the Website

Ensure that <aarmitan>.42.fr points to your local IP address.

Open in browser:

https://<aarmitan>.42.fr

WordPress admin panel:

https://<aarmitan>.42.fr/wp-admin

---

## Credentials

Credentials are stored in:

- srcs/.env  
- secrets/ directory  

No credentials are stored in Dockerfiles.

---

## Checking Services

Check running containers:

docker compose ps

View logs:

docker compose logs

List volumes:

docker volume ls

Persistent data is stored in:

/home/<aarmitan>/data
