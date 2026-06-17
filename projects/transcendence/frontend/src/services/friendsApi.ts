import { api } from './api';
import type { User, FriendRequest } from '../types';

interface FriendRequestsResponse {
    requests?: FriendRequest[];
}

export type FriendRequestDecision = 'ACCEPT' | 'DECLINE';

export async function searchUsers(query: string): Promise<User[]> {
    const response = await api.get<User[]>('/users/search', {
        params: { q: query },
    });

    return response.data;
}

export async function getFriends(): Promise<User[]> {
    const response = await api.get<User[]>('/friends');

    return response.data;
}

export async function getFriendRequests(): Promise<FriendRequest[]> {
    const response = await api.get<FriendRequestsResponse>('/friends/requests');

    return response.data.requests ?? [];
}

export async function sendFriendRequest(toUserId: number): Promise<FriendRequest | null> {
    const response = await api.post<FriendRequest>(
        '/friends/requests',
        { userId: toUserId },
    );

    return response.data;
}

export async function updateFriendRequestStatus(
    requestId: number,
    decision: FriendRequestDecision,
): Promise<void> {
    const status = decision === 'ACCEPT' ? 'accepted' : 'refused';

    await api.put(`/friends/requests/${requestId}`, { status });
}

export async function removeFriend(friendId: number): Promise<void> {
    await api.delete(`/friends/${friendId}`);
}

export async function getFriendPetCustomizations(userId: number) {
    const response = await api.get(`/pets?q=${userId}`);
    return response.data;
}
