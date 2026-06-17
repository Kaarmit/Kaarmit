import { useCallback, useEffect, useMemo, useState } from 'react';
import type { FriendPresence, User, FriendRequest } from '../types';
import {
    getFriendRequests,
    getFriends,
    removeFriend as removeFriendApi,
    searchUsers as searchUsersApi,
    sendFriendRequest,
    updateFriendRequestStatus
} from '../services/friendsApi';
import { useSocket } from './useSocket';

interface FriendStatusPayload { // For online/offline events, the backend might send us just the user ID, or a more detailed object. We want to be flexible in handling different possible payload structures.
    userId?: number;
    id?: number;
}

interface FriendsPresencePayload { // For presence updates, the backend might send us a list of online user IDs, or a list of online user objects, or both. We want to be flexible in handling different possible payload structures.
    onlineUserIds?: number[];
    onlineUsers?: Array<{ id: number }>;
}

interface FriendMutationPayload { // For both added and removed events. Here we try to be flexible with the payload structure to accommodate different possible backend implementations. So if wwe want to add a friend, the backend might send us the new friend's user object, or just their ID, or some combination of both. Same for removal.
    friendId?: number;
    userId?: number;
    id?: number;
    friend?: User;
    user?: User;
}

const mapUsersToPresence = (users: User[], onlineIds: Set<number>): FriendPresence[] =>
    users.map(user => ({
        ...user,
        isOnline: onlineIds.has(user.id),
    }));

export function useFriendsPresence(token?: string, currentUserId?: number) {
    const initialOnlineIds = useMemo(() => new Set<number>(), []);
    const effectiveCurrentUserId = currentUserId ?? 0;

    const [friends, setFriends] = useState<FriendPresence[]>([]);
    const [pendingRequests, setPendingRequests] = useState<FriendRequest[]>([]);
    const [outgoingRequests, setOutgoingRequests] = useState<number[]>([]);
    const [loading, setLoading] = useState(false);

    const { isConnected, emit, on, off } = useSocket({ autoConnect: true, token });

    useEffect(() => {
        let mounted = true;

        const loadSocialData = async () => {
            setLoading(true);
            try {
                const [apiFriends, apiPendingRequests] = await Promise.all([
                    getFriends(),
                    getFriendRequests(),
                ]);

                if (!mounted) return;
                
                console.log('===DEBUG: Loaded friends from API:', apiFriends);
                console.log('currentUserId:', currentUserId);
                console.log('all pending requests from API:', apiPendingRequests);
                console.log('filtered pending requests for current user:', apiPendingRequests.filter(request => request.status === 'PENDING' && request.toUserId === currentUserId));

                setFriends(mapUsersToPresence(apiFriends, initialOnlineIds)); // Use API data for friends
                setPendingRequests(apiPendingRequests.filter(request => request.status === 'PENDING' && request.toUserId === effectiveCurrentUserId)); // Use API data for pending requests
            } catch {
                if (!mounted) return;
                setFriends([]);
                setPendingRequests([]);
            } finally {
                if (mounted) {
                    setLoading(false);
                }
            }
        };

        loadSocialData();
        return () => {
            mounted = false;
        };
    }, [initialOnlineIds, currentUserId]);

    useEffect(() => {
        const handlePresence = (payload: FriendsPresencePayload) => {
            const onlineIds = new Set<number>([
                ...(payload.onlineUserIds ?? []),
                ...((payload.onlineUsers ?? []).map(user => user.id)),
            ]);

            setFriends(prev =>
                prev.map(friend => ({
                    ...friend,
                    isOnline: onlineIds.has(friend.id),
                })),
            );
        };

        const handleOnline = (payload: FriendStatusPayload) => {
            const friendId = payload.userId ?? payload.id;
            if (!friendId) return;

            setFriends(prev =>
                prev.map(friend =>
                    friend.id === friendId
                        ? { ...friend, isOnline: true }
                        : friend,
                ),
            );
        };

        const handleOffline = (payload: FriendStatusPayload) => {
            const friendId = payload.userId ?? payload.id;
            if (!friendId) return;

            setFriends(prev =>
                prev.map(friend =>
                    friend.id === friendId
                        ? { ...friend, isOnline: false }
                        : friend,
                ),
            );
        };

        const handleFriendAdded = (payload: FriendMutationPayload) => {
            const friendUser = payload.friend ?? payload.user;
            const friendId = payload.friendId ?? payload.userId ?? payload.id ?? friendUser?.id;

            if (!friendId) {
                return;
            }

            setFriends(prev => {
                const alreadyFriend = prev.some(friend => friend.id === friendId);
                if (alreadyFriend) {
                    return prev;
                }

                if (!friendUser) {
                    return prev;
                }

                return [
                    ...prev,
                    {
                        ...friendUser,
                        isOnline: initialOnlineIds.has(friendUser.id),
                    },
                ];
            });
        };

        const handleFriendRemoved = (payload: FriendMutationPayload) => {
            const friendId = payload.friendId ?? payload.userId ?? payload.id ?? payload.friend?.id ?? payload.user?.id;
            if (!friendId) {
                return;
            }

            setFriends(prev => prev.filter(friend => friend.id !== friendId));
        };

        const handleFriendRequest = (payload: { request?: FriendRequest } | FriendRequest) => {
            const request = (payload as any).request ?? (payload as FriendRequest);
            if (!request) return;

            if (request.toUserId !== effectiveCurrentUserId) return;

            setPendingRequests(prev => {
                if (prev.some(r => r.id === request.id)) return prev;
                return [request, ...prev];
            });
        };

		// Handlers use functional state updates(setFriends(prev => ...)) so friends is not needed in the dependency array.
		// Having it caused all listeners to be torn down and re - registered on every isOnline toggle, creating a feedback loop.

        on<FriendsPresencePayload>('friends:presence', handlePresence);
        on<FriendStatusPayload>('friend:online', handleOnline);
        on<FriendStatusPayload>('friend:offline', handleOffline);
        on<FriendMutationPayload>('friend:added', handleFriendAdded);
        on<FriendMutationPayload>('friend:removed', handleFriendRemoved);
        on<any>('friend:request', handleFriendRequest);
        const handleRequestRefused = (payload: { request?: FriendRequest } | FriendRequest) => {
            const request = (payload as any).request ?? (payload as FriendRequest);
            if (!request) return;

            const toUserId = (request as any).toUserId ?? request.toUser?.id;
            if (!toUserId) return;

            setOutgoingRequests(prev => prev.filter(id => id !== toUserId));
            // Optionally inform the user
            console.log('[Realtime] Your friend request was refused:', request);
        };

        on<any>('friend:request:refused', handleRequestRefused);

        return () => {
            off('friends:presence', handlePresence as (...args: unknown[]) => void);
            off('friend:online', handleOnline as (...args: unknown[]) => void);
            off('friend:offline', handleOffline as (...args: unknown[]) => void);
            off('friend:added', handleFriendAdded as (...args: unknown[]) => void);
            off('friend:removed', handleFriendRemoved as (...args: unknown[]) => void);
            off('friend:request', handleFriendRequest as (...args: unknown[]) => void);
            off('friend:request:refused', handleRequestRefused as (...args: unknown[]) => void);
        };
    }, [isConnected, emit, on, off, effectiveCurrentUserId /*friends, initialOnlineIds*/]); // include current user id for request filtering

	// Decoupled from the listener effect to avoid re-subscribing on every presence update.
	// Uses friends.length as dependency instead of the full array so it only re-fires when 
	// friends are added or removed. The friends.length === 0 guard prevents sending an 
	// empty friendIds before the API has loaded, which caused a race condition on page 
	// refresh in Chrome.
	useEffect(() => {
		if (!isConnected || friends.length === 0) return;
		const friendIds = friends.map(f => f.id);
		emit('friends:subscribe', { friendIds });
		emit('friends:presence:request', { friendIds });
	}, [isConnected, friends.length, emit]); 

    const onlineCount = friends.filter(friend => friend.isOnline).length;

    const searchUsers = useCallback(async (query: string): Promise<User[]> => {
        const search = query.trim();
        if (!search) {
            return [];
        }
        const users = await searchUsersApi(search);
        return users;
    }, []);

    const addFriend = async (user: User): Promise<void> => {
        try {
            // Prevent duplicate sends client-side when we already tracked an outgoing request
            if (outgoingRequests.includes(user.id)) return;

            const sent = await sendFriendRequest(user.id);
            if (sent) {
                setOutgoingRequests(prev => (prev.includes(user.id) ? prev : [...prev, user.id]));
            }
        } catch {
        }
    };

    const acceptRequest = async (requestId: number): Promise<void> => {
        const requestToAccept = pendingRequests.find(request => request.id === requestId);

        try {
            await updateFriendRequestStatus(requestId, 'ACCEPT');
        } catch {
        }

        setPendingRequests(prev => prev.filter(request => request.id !== requestId));

        const fromUser = requestToAccept?.fromUser;
        if (fromUser) {
            return;
        }

        try {
            const refreshedFriends = await getFriends();
			setFriends(prev => {
				const currentOnlineIds = new Set(prev.filter(f => f.isOnline).map(f => f.id));
				return mapUsersToPresence(refreshedFriends, currentOnlineIds);
			}); 
        } catch {
        }
    };

    const refuseRequest = async (requestId: number): Promise<void> => {
        const previousRequests = pendingRequests;
        setPendingRequests(prev => prev.filter(request => request.id !== requestId));

        try {
            await updateFriendRequestStatus(requestId, 'DECLINE');
        } catch {
            setPendingRequests(previousRequests);
        }
    };

    const removeFriend = async (userId: number): Promise<void> => {
        const previousFriends = friends;
        setFriends(prev => prev.filter(friend => friend.id !== userId));

        try {
            await removeFriendApi(userId);
        } catch {
            setFriends(previousFriends);
        }
    };

    return {
        friends,
        onlineCount,
        isConnected,
        loading,
        pendingRequests,
        outgoingRequests,
        searchUsers,
        addFriend,
        acceptRequest,
        refuseRequest,
        removeFriend,
    };
}

export default useFriendsPresence;
