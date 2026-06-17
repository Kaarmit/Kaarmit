import { io, Socket } from 'socket.io-client';

const SOCKET_URL = '';

type SocketEvent = 'connected' | 'disconnected';

class SocketService {
    private socket: Socket | null = null;
    private token: string | null = null;
    private listeners: Map<SocketEvent, Set<() => void>> = new Map();

    private emit_internal(event: SocketEvent) {
        this.listeners.get(event)?.forEach(cb => cb());
    }

    onConnectionChange(event: SocketEvent, cb: () => void): () => void {
        if (!this.listeners.has(event)) this.listeners.set(event, new Set());
        this.listeners.get(event)?.add(cb);
        return () => this.listeners.get(event)?.delete(cb);
    }

    connect(token?: string): Socket {
        console.log('[SocketService] connect appelé, déjà connecté:', this.socket?.connected);
        if (token) {
            this.token = token;
        }

        if (this.socket && token && token !== this.token) {
            this.socket.disconnect();
            this.socket = null;
        }

        //if (this.socket?.connected) {
        //    return this.socket;
        if (this.socket) {
            const nextAuth = {
                ...(typeof this.socket.auth === 'object' && this.socket.auth !== null ? this.socket.auth : {}),
                token: this.token,
            };

            this.socket.auth = nextAuth;

            if (!this.socket.connected && this.token) {
                this.socket.connect();
            }

            return this.socket;
        }

        this.socket = io(SOCKET_URL, {
            auth: {
                token: this.token,
            },
            autoConnect: !!this.token,
            transports: ['websocket', 'polling'], // we try websocket first, then fallback to polling if needed
            reconnection: true,
            reconnectionAttempts: 5,
            reconnectionDelay: 1000,
        });

        if (this.token && !this.socket.connected) {
            this.socket.connect();
        }

        this.socket.on('connect', () => {
            console.log('Socket connected:', this.socket?.id);
            this.emit_internal('connected');
        });

        this.socket.on('disconnect', (reason: string) => {
            console.log('Socket disconnected:', this.socket?.id, 'reason:', reason);
            this.emit_internal('disconnected');
        });

        this.socket.on('connect_error', (error: Error) => {
            console.error('Socket connection error:', error);
        });

        return this.socket;
    }

    disconnect(): void {
        if (this.socket) {
            this.socket.disconnect();
            this.socket = null;
            this.token = null;
            this.emit_internal('disconnected');
        }
        this.token = null;
    }

    getSocket(): Socket | null {
        return this.socket;
    }

    isConnected(): boolean {
        return this.socket?.connected ?? false;
    }

    emit(event: string, data?: unknown): void {
        if (this.socket) {
            this.socket.emit(event, data);
        } else {
            console.warn(`[SocketService] Socket not initialized when emitting "${event}"`);
        }
    }

    on<T>(event: string, callback: (data: T) => void): void {
        this.socket?.on(event, callback);
    }

    off(event: string, callback?: (...args: unknown[]) => void): void {
        this.socket?.off(event, callback);
    }
}

export const socketService = new SocketService();
export default socketService;
