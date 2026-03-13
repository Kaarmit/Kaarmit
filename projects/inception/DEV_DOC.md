# Developer Documentation

## Prerequisites

- Linux Virtual Machine
- Docker
- Docker Compose v2
- Make

---

## Project Structure

Makefile  
secrets/  
srcs/  
  ├── docker-compose.yml  
  ├── .env  
  └── requirements/  
      ├── mariadb/  
      ├── nginx/  
      └── wordpress/  

Each service contains:
- Dockerfile
- Configuration files
- Optional entrypoint scripts

---

## Environment Setup

1. Clone the repository.
2. Create required secret files in secrets/.
3. Ensure the directory exists:

/home/<aarmitan>/data

---

## Build and Launch

Build images:

docker compose build

Launch containers:

docker compose up -d

Using Makefile:

make  
make up

---

## Container Management

List containers:

docker compose ps

View logs:

docker compose logs -f

Access a container shell:

docker exec -it <container_name> sh

Stop everything:

docker compose down

Rebuild without cache:

docker compose build --no-cache

---

## Data Persistence

Project data is stored in two Docker named volumes:

- MariaDB data volume
- WordPress files volume

These volumes are bound to directories under:

/home/aarmitan/data

This ensures persistence of data even when:
- containers are restarted
- containers are removed and recreated
- images are rebuilt

Invariant:
As long as the volumes are not deleted, the database content and WordPress files remain intact.

## Networking

- Dedicated Docker bridge network
- Services communicate via service names
- Only NGINX exposes port 443

---

## Initialization Logic

MariaDB:
- First boot initializes database and users
- Subsequent boots skip initialization (idempotent behavior)

WordPress:
- Waits for MariaDB
- Generates wp-config.php if missing
- Skips installation if already configured

---

## Debugging

Check service logs:

docker compose logs mariadb  
docker compose logs wordpress  
docker compose logs nginx  

Inspect volumes:

docker volume inspect <volume_name>

Check listening ports:

ss -lntp
