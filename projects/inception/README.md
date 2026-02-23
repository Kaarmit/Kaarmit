*This project has been created as part of the 42 curriculum by <aarmitan>.*

# Inception

## Description

Inception is a system administration project that consists of building a secure, containerized web infrastructure using Docker Compose inside a virtual machine.

The stack is composed of three isolated services:

- NGINX (TLSv1.2 or TLSv1.3 only) — single public entrypoint on port 443
- WordPress with PHP-FPM — application layer
- MariaDB — database layer

The infrastructure enforces:

- One Dockerfile per service
- No prebuilt service images (except base Alpine/Debian)
- Dedicated Docker network
- Two Docker named volumes for persistent storage
- Environment variables stored in `.env`
- No passwords inside Dockerfiles
- Automatic restart on crash

The goal is to design a reproducible, isolated, and persistent architecture.

---

## Architecture Overview

Client  
→ HTTPS (443)  
→ NGINX  
→ PHP-FPM (9000)  
→ WordPress  
→ MariaDB (3306)

Persistence:
- Database volume
- WordPress files volume

Isolation:
- Dedicated Docker bridge network
- Only NGINX exposes port 443

---

## Design Choices

### Virtual Machines vs Docker

Virtual Machines virtualize hardware and run a full OS per instance. They provide strong isolation but consume more resources.

Docker virtualizes at the process level using the host kernel. It is lightweight, faster to start, and image-based.

In this project:
- The VM provides system-level isolation.
- Docker provides service-level isolation and reproducibility.

### Secrets vs Environment Variables

Environment variables are convenient but visible in container metadata.

Docker secrets are mounted as files and are safer for sensitive credentials.

This project uses `.env` for configuration and Docker secrets for confidential data.

### Docker Network vs Host Network

Host network removes isolation and directly exposes services to the host stack.

Docker networks provide internal DNS resolution and service isolation.

This project requires a dedicated Docker network. Host networking is forbidden.

### Docker Volumes vs Bind Mounts

Bind mounts directly map host paths and create tight coupling with the host filesystem.

Named volumes are managed by Docker and improve portability and isolation.

This project requires named volumes storing data in:

/home/<aarmitan>/data

---

## Instructions

Build images:

make

Start the stack:

make up

Stop the stack:

make down

Rebuild everything:

make re

Check containers:

docker compose ps

Access the website:

https://<aarmitan>.42.fr

---

## Resources

- Docker Documentation  
- Docker Compose Documentation  
- NGINX Documentation  
- MariaDB Documentation  
- WordPress and PHP-FPM Documentation  

---

## AI Usage

AI tools were used to structure documentation and review architectural decisions.  
All generated content was manually validated and understood before integration.

