import { useState, useCallback, useEffect, useRef } from 'react';
import type { ChatMessage } from '../types';
import socketService from '../services/socket';
import { api } from '../services/api';

type MessagesByFriend = Record<number, ChatMessage[]>;
type DraftByFriend = Record<number, string>;
type ConvByFriend = Record<number, number>;

export function useChat(_currentUserId: number, _currentUsername: string) {
    const [messagesByFriend, setMessagesByFriend] = useState<MessagesByFriend>({});
    const [draftByFriend, setDraftByFriend] = useState<DraftByFriend>({});
    const convByFriendRef = useRef<ConvByFriend>({});

    useEffect(() => {
        const register = () => {
            const sock = socketService.getSocket();
            if (!sock) {
                setTimeout(register, 200);
                return;
            }

            const handleNewMessage = (msg: any) => {
                console.log('[message:new] reçu:', msg.id, msg.content, 'conversationId:', msg.conversationId);
                console.log('[message:new] convByFriendRef:', convByFriendRef.current);
                const entry = Object.entries(convByFriendRef.current)
                    .find(([_, cId]) => cId === msg.conversationId);
                if (!entry) return;
                const fId = Number(entry[0]);

                setMessagesByFriend((prev) => {
                    const existing = prev[fId] ?? [];
                    if (existing.some((m) => m.id === msg.id)) return prev;
                    return {
                        ...prev,
                        [fId]: [...existing, {
                            id: msg.id,
                            userId: msg.senderId,
                            username: msg.sender.username,
                            message: msg.content,
                            timestamp: new Date(msg.createdAt),
                        }],
                    };
                });
            };

            sock.on('message:new', handleNewMessage);
        };

        register();
    }, []);

    const openConversation = useCallback(async (friendId: number) => {
        if (convByFriendRef.current[friendId]) return;

        try {
            const { data: conversation } = await api.post('/conversations', { friendId });
            const conversationId: number = conversation.id;
            convByFriendRef.current[friendId] = conversationId;

            const socket = socketService.getSocket();
            if (socket) {
                socket.emit('conversation:join', conversationId);
            }

            const { data: history } = await api.get(`/conversations/${conversationId}/messages`);

            setMessagesByFriend((prev) => ({
                ...prev,
                [friendId]: history.map((msg: any) => ({
                    id: msg.id,
                    userId: msg.senderId,
                    username: msg.sender.username,
                    message: msg.content,
                    timestamp: new Date(msg.createdAt),
                })),
            }));

        } catch (err) {
            console.error('[useChat] openConversation error:', err);
        }
    }, []);

    const setNewMessage = (friendId: number, value: string) => {
        setDraftByFriend((prev) => ({ ...prev, [friendId]: value }));
    };

    const sendMessage = useCallback(async (friendId: number, content?: string) => {
        const draft = (content ?? draftByFriend[friendId] ?? '').trim();
        if (draft === '') return;

        let conversationId = convByFriendRef.current[friendId];
        if (!conversationId) {
            await openConversation(friendId);
            conversationId = convByFriendRef.current[friendId];
            if (!conversationId) {
                console.error('[useChat] Pas de conversationId pour cet ami');
                return;
            }
        }

        const socket = socketService.getSocket();
        if (!socket) {
            console.error('[useChat] Socket non connecté');
            return;
        }

        setDraftByFriend((prev) => ({ ...prev, [friendId]: '' }));

        socket.emit('message:send', { conversationId, content: draft }, (response: any) => {
            console.log('[ack] reçu:', response?.message?.id, response?.message?.content);
            if (response?.error) {
                console.error('[useChat] Erreur envoi:', response.error);
                setDraftByFriend((prev) => ({ ...prev, [friendId]: draft }));
                return;
            }

            const msg = response.message;
            setMessagesByFriend((prev) => {
                const existing = prev[friendId] ?? [];
                if (existing.some((m) => m.id === msg.id)) return prev;
                return {
                    ...prev,
                    [friendId]: [...existing, {
                        id: msg.id,
                        userId: msg.senderId,
                        username: msg.sender.username,
                        message: msg.content,
                        timestamp: new Date(msg.createdAt),
                    }],
                };
            });
        });
    }, [draftByFriend, openConversation]);

    return {
        messagesByFriend,
        draftByFriend,
        openConversation,
        setNewMessage,
        sendMessage,
    };
}