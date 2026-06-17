*This project has been created as part of the 42 curriculum by vihane, vgalmich, cldalmaz, aarmitan and tnedel.*

# ft_transcendence - Nekotchi 3D

> A multiplayer 3D Tamagotchi-inspired web application built with modern full-stack technologies, real-time systems and interactive gameplay.

# Description

**Nekotchi 3D** is a social multiplayer web application combining:

* virtual pet simulation
* real-time multiplayer interactions
* 3D graphics
* mini-games
* customization systems
* live chat features

The project reimagines the classic Tamagotchi experience inside a modern web application with an immersive stylised 3D environment.

Each player adopts a floating virtual companion called a **Nekotchi** and must keep it alive by managing its needs, interacting with other players, and playing mini-games.

The project focuses on:

* full-stack web engineering
* real-time networking
* multiplayer synchronization
* 3D rendering on the web
* authentication and security
* collaborative software development

# Features List

## Nekotchi System

At the center of the experience is a fully interactive floating 3D pet.

Each Nekotchi has several survival stats:

1. Happiness
2. Hunger
3. Sleep
4. Energy

If one or more stats fall below a critical threshold, the pet dies and triggers a **game over** state.

The pet system is directly connected to gameplay and player activity.

---

## Mini-Games

The project currently includes two mini-games:

### I. Course

A multiplayer racing mini-game focused on:

* movement
* speed
* real-time synchronization
* multiplayer interactions

### II. FoodCatch

A reflex-based mini-game where players catch food items to feed their Nekotchi and improve its survival stats.

These games directly affect the evolution and survival of the pet.

---

## Multiplayer Features

Nekotchi 3D integrates several real-time systems using WebSockets.

Implemented multiplayer features include:

* synchronized gameplay
* live player interactions
* real-time chat
* online/offline presence
* multiplayer game synchronization
* spectator mode for ongoing games

The project supports multiple connected users simultaneously.

---

## Chat & Social Features

Players can communicate and interact directly inside the application.

Current systems include:

* live messaging
* private conversations
* friends system
* online status
* profile pages
* persistent conversations

---

## Customization System

Players can personalize several parts of their experience.

### Nekotchi Customization

* cat color
* pet name
* Tamagotchi shell color

### Interface Customization

* cursor paw color
* dynamic backgrounds
* personalized visual themes

---

## Authentication & Security

The backend implements a modern authentication system based on JWT.

Implemented security features include:

* password hashing using bcrypt
* protected API routes
* HTTPS support
* JWT authentication
* Two-Factor Authentication (2FA)

2FA is implemented using TOTP authentication compatible with:

* Google Authenticator
* Authy
* Microsoft Authenticator

# Technical Stack

## Frontend

The frontend is built using:

* React 18
* Vite
* TypeScript
* Three.js
* React Three Fiber
* Drei
* Socket.IO Client
* Framer Motion
* React Router
* Axios

### Frontend Goals

The frontend focuses on:

* immersive 3D rendering
* responsive gameplay
* real-time interactions
* smooth animations
* modular reusable components

---

## Backend

The backend architecture uses:

* Node.js
* Express
* TypeScript
* Socket.IO
* Prisma ORM
* JWT
* bcrypt
* speakeasy
* qrcode

### Backend Responsibilities

The backend handles:

* authentication
* multiplayer synchronization
* real-time communication
* game state management
* friend systems
* conversations
* persistence layer
* API security

---

## Database

The project uses:

* PostgreSQL
* Prisma ORM
* Prisma migrations

### Persisted Data

Current persisted entities include:

* users
* friend requests
* conversations
* messages
* read receipts
* Nekotchi customization data
* 2FA configuration

---

## DevOps & Infrastructure

Infrastructure technologies include:

* Docker
* Docker Compose
* HTTPS local certificates
* environment variables

---

## Technical Choices Justification

* PostgreSQL was chosen for its reliability and strong relational data support.
* Prisma ORM was selected to simplify database management and migrations.
* Socket.IO was used to handle real-time multiplayer synchronization and chat systems.
* React Three Fiber was chosen to integrate Three.js smoothly inside React components.
* Docker was used to simplify development environment setup and team collaboration.

# Database Schema

```text
Frontend (React / Vite / Three.js)
        │
        │ HTTPS + WebSockets
        ▼
Backend API (Express + Socket.IO)
        │
        ▼
Prisma ORM
        │
        ▼
PostgreSQL Database
```

The database mainly stores:

* user accounts
* authentication data
* conversations and messages
* friend relationships
* Nekotchi customization data
* multiplayer game information

---

## Relationships

* One user can send multiple messages.
* One conversation can contain multiple messages.
* Users can exchange friend requests.
* User customization data is linked to player accounts.

# Modules

The project targets the following modules from the ft_transcendence subject:

## Major Modules (2 points each)

| Module | Points |
| --- | --- |
| Frontend + Backend Frameworks | 2 |
| Real-time WebSockets Features | 2 |
| User Interaction System | 2 |
| Standard User Management | 2 |
| Complete Multiplayer Game | 2 |
| Advanced 3D Graphics | 2 |
| Introduce an AI Opponent for games | 2 |

### Frontend + Backend Frameworks

Implemented using React, Express and TypeScript to create a modern full-stack architecture.

### Real-time WebSockets Features

Implemented using Socket.IO for multiplayer synchronization and live chat systems.

### User Interaction System

Implemented through chat systems, profile pages, friend systems and multiplayer interactions.

### Standard User Management

Implemented with JWT authentication, protected routes and user account systems.

### Complete Multiplayer Game

Implemented with synchronized mini-games and multiplayer sessions.

### Advanced 3D Graphics

Implemented using Three.js and React Three Fiber.

### Introduce an AI Opponent for games

Implemented using basic game AI behaviors for mini-game interactions.

---

### Major Modules Total

**14 points**

---

## Minor Modules (1 point each)

| Module | Points |
| --- | --- |
| Prisma ORM | 1 |
| Two-Factor Authentication (2FA) | 1 |
| Game Customization | 1 |
| Spectator Mode | 1 |
| Additional Browser Support | 1 |

### Prisma ORM

Implemented using Prisma migrations and schema management.

### Two-Factor Authentication (2FA)

Implemented using TOTP authentication with QR code support.

### Game Customization

Implemented through Nekotchi personalization and UI themes.

### Spectator Mode

Implemented using synchronized live game observation systems.

### Additional Browser Support

Implemented through responsive frontend testing and compatibility adjustments.

---

### Minor Modules Total

**5 points**

---

## Total Target

**19 points**

# Team Information

## Viviane && Véronique

### Roles

* Frontend Developer
* Technical Lead

### Responsibilities

* UI/UX implementation
* 3D integration
* gameplay interfaces
* customization systems
* spectator systems

---

## Alexis && Thibault

### Roles

* Backend Developer
* Technical Lead

### Responsibilities

* backend architecture
* Express APIs
* Socket.IO systems
* multiplayer synchronization
* database integration
* security

---

## Clio

### Roles

* Fullstack Developer
* Security
* Project Organization

### Responsibilities

* authentication systems
* JWT security
* 2FA implementation
* project coordination
* documentation
* AI integration

# Individual Contributions

## Viviane

* Implemented 3D rendering systems.
* Worked on customization systems and gameplay interfaces.
* Participated in spectator mode implementation.

---

## Véronique

* Worked on frontend integration and visual customization.
* Participated in browser compatibility improvements.
* Assisted with UI/UX polishing.

---

## Alexis

* Implemented backend architecture and APIs.
* Worked on Socket.IO synchronization systems.
* Managed Prisma database integration.

---

## Thibault

* Worked on multiplayer systems and game synchronization.
* Implemented several gameplay systems and AI behaviors.

---

## Clio

* Implemented authentication and security systems.
* Managed JWT and 2FA integration.
* Organized project coordination and documentation.
* Creation of AI opponents

# Project Management

The project is organized using:

* GitHub branches and pull requests
* Discord communication
* shared task distribution
* feature-based development
* regular synchronization meetings
* collaborative code reviews

The team follows a collaborative workflow where each member contributes to both mandatory systems and selected modules.

# Security

The application integrates multiple security layers.

Implemented protections include:

* HTTPS local certificates
* JWT authentication
* password hashing with bcrypt
* protected API routes
* WebSocket authentication
* 2FA support
* Prisma data validation

Security and authentication systems are actively reviewed and tested during development.

# Instructions

## Requirements

Before starting the project, make sure the following tools are installed:

* Node.js >= 18
* npm >= 9
* PostgreSQL >= 15
* Docker >= 24 (recommended)

# Clone Repository

```bash
git clone <repository_url>
cd ft_transcendence
```

# Docker Setup

Run the complete application:

```bash
docker compose up --build
```

## Services

| Service | URL |
| --- | --- |
| Frontend | https://localhost:8443 |
| Backend API | https://localhost:3000 |

---

# Backend Setup

```bash
cd backend
npm install
```

---

## Environment Variables

Create a `.env` file inside the backend directory:

```env
DATABASE_URL="postgresql://admin:admin@localhost:5432/ft_transcendence"
JWT_SECRET="your_secret"
```

---

## Prisma Setup

```bash
npx prisma generate
npx prisma migrate dev
```

---

## Start Backend

```bash
npm run dev
```

# Frontend Setup

```bash
cd frontend
npm install
npm run dev
```

# Usage Example

1. Create an account.
2. Configure your Nekotchi.
3. Join multiplayer mini-games.
4. Interact with other players through chat systems.
5. Keep your Nekotchi alive by managing its needs.

# Development Notes

The project is still evolving and several systems are continuously improved.

Current development focuses include:

* gameplay balancing
* multiplayer synchronization
* spectator systems
* UI polish
* browser compatibility
* additional game systems

# Educational Goals

This project was developed to explore advanced software engineering topics:

* full-stack architecture
* real-time networking
* multiplayer synchronization
* web security
* database design
* 3D rendering on the web
* DevOps workflows
* collaborative development

# Future Improvements

Possible future additions include:

* additional mini-games
* AI opponents
* Nekotchi evolution systems
* achievements and progression
* matchmaking systems
* inventory systems
* mobile optimization

# Resources

## Documentation

* Prisma ORM — https://www.prisma.io/docs
* Socket.IO — https://socket.io/docs/v4
* PostgreSQL — https://www.postgresql.org/docs
* React Three Fiber — https://docs.pmnd.rs/react-three-fiber
* Three.js — https://threejs.org/docs
* Express — https://expressjs.com

---

## Inspiration

* Tamagotchi
* virtual pet games
* multiplayer browser games

---

## AI Usage

AI tools were used to assist with:

* technical research
* debugging
* architecture brainstorming
* Prisma troubleshooting
* Socket.IO synchronization research
* documentation improvements

All generated content was reviewed, tested and manually validated before integration into the project.

# License

This project was developed as part of the 42 School curriculum.