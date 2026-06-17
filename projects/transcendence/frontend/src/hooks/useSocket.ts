import { useEffect, useState, useCallback, useRef } from 'react';
import { Socket } from 'socket.io-client';
import socketService from '../services/socket';

interface UseSocketOptions {
    autoConnect?: boolean;
    token?: string;
}

export function useSocket(options: UseSocketOptions = {}) {
    const { autoConnect = false, token } = options;
    const [isConnected, setIsConnected] = useState(() => socketService.isConnected());
    const [socket, setSocket] = useState<Socket | null>(() => socketService.getSocket());
    const listenersRef = useRef<Map<string, Set<(...args: unknown[]) => void>>>(new Map());

    useEffect(() => {
         if (autoConnect) {
            socketService.connect(token);
            setSocket(socketService.getSocket());
        }

        // Always sync connection state from the service, regardless of autoConnect
        const handleConnect = () => {
            setIsConnected(true);
            setSocket(socketService.getSocket());
        };
        const handleDisconnect = () => {
            setIsConnected(false);
            setSocket(null);
        };

        const unsubConnect = socketService.onConnectionChange('connected', handleConnect);
        const unsubDisconnect = socketService.onConnectionChange('disconnected', handleDisconnect);

        // Sync immediately in case already connected
        if (socketService.isConnected()) {
            setIsConnected(true);
            setSocket(socketService.getSocket());
        }

        return () => {
            unsubConnect();
            unsubDisconnect();
        };
    }, [autoConnect, token]);

    const emit = useCallback((event: string, data?: unknown) => {
        socketService.emit(event, data);
    }, []);

    const on = useCallback(<T,>(event: string, callback: (data: T) => void) => {
        const sock = socketService.getSocket();
        if (sock) {
            sock.on(event, callback as (...args: unknown[]) => void);

            // Track listeners for cleanup
            if (!listenersRef.current.has(event)) {
                listenersRef.current.set(event, new Set());
            }
            listenersRef.current.get(event)?.add(callback as (...args: unknown[]) => void);
        }
    }, []);

    const off = useCallback((event: string, callback?: (...args: unknown[]) => void) => {
        const sock = socketService.getSocket();
        if (sock) {
            sock.off(event, callback);
            if (callback) {
                listenersRef.current.get(event)?.delete(callback);
            } else {
                listenersRef.current.delete(event);
            }
        }
    }, []);

    const connect = useCallback((newToken?: string) => {
        const sock = socketService.connect(newToken || token);
        setSocket(sock);
        return sock;
    }, [token]);

    const disconnect = useCallback(() => {
        // Clean up all tracked listeners
        listenersRef.current.forEach((callbacks, event) => {
            callbacks.forEach(cb => socketService.off(event, cb));
        });
        listenersRef.current.clear();
        socketService.disconnect();
        setSocket(null);
        setIsConnected(false);
    }, []);

    // Cleanup on unmount
    useEffect(() => {
        return () => {
            listenersRef.current.forEach((callbacks, event) => {
                callbacks.forEach(cb => socketService.off(event, cb));
            });
            listenersRef.current.clear();
        };
    }, []);

    return {
        socket,
        isConnected,
        emit,
        on,
        off,
        connect,
        disconnect,
    };
}

export default useSocket;
