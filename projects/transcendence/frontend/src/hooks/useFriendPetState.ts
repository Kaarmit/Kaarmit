import { useEffect, useState } from 'react';
import { api } from '../services/api';
import { useSocket } from './useSocket';
import type { PetState, CatType } from '../types';

interface FriendPetData {
  pet: PetState | null;
  catType: CatType;
  color: string;
  background: string;
  loading: boolean;
  error: string | null;
}

export function useFriendPetState(friendId: number | null) {
  const [data, setData] = useState<FriendPetData>({
    pet: null,
    catType: 'beigecat',
    color: '#FF69B4',
    background: '/backgrounds/city.png',
    loading: false,
    error: null,
  });

  const { emit, on, off, isConnected } = useSocket({ autoConnect: true });

  // Initial load: fetch from API (works for both online and offline friends)
  useEffect(() => {
    let canceled = false;

    const loadPetData = async () => {
      if (!friendId) {
        setData({
          pet: null,
          catType: 'beigecat',
          color: '#FF69B4',
          background: '/backgrounds/city.png',
          loading: false,
          error: null,
        });
        return;
      }

      setData((prev: FriendPetData) => ({ ...prev, loading: true, error: null }));

      try {
        // Fetch customizations and pet state in parallel
        const [customRes, stateRes] = await Promise.all([
          api.get(`/pets?q=${friendId}`),
          api.get(`/pets/state?q=${friendId}`),
        ]);

        if (canceled) return;

        const petState: PetState = {
          name: customRes.data?.catName || `Friend's Pet`,
          hunger: stateRes.data?.hunger ?? 50,
          happiness: stateRes.data?.happiness ?? 70,
          cleanliness: stateRes.data?.cleanliness ?? 60,
          energy: stateRes.data?.energy ?? 75,
          lastFed: stateRes.data?.lastFed,
          lastPlayed: stateRes.data?.lastPlayed,
          lastCleaned: stateRes.data?.lastCleaned,
          lastSlept: stateRes.data?.lastSlept,
          id: stateRes.data?.id,
        };

        setData((prev: FriendPetData) => ({
          ...prev,
          pet: petState,
          catType: (customRes.data?.cat || 'beigecat') as CatType,
          color: customRes.data?.color || '#FF69B4',
          background: customRes.data?.background || '/backgrounds/city.png',
          loading: false,
        }));
      } catch (err: any) {
        if (canceled) return;
        setData((prev: FriendPetData) => ({
          ...prev,
          pet: null,
          loading: false,
          error: err?.message ?? 'Failed to load pet data',
        }));
      }
    };

    loadPetData();
    return () => {
      canceled = true;
    };
  }, [friendId]);

  useEffect(() => {
    if (!friendId || !isConnected) return;

    // (Re)send subscription every time we connect or reconnect
    emit('pet:subscribe', { userId: friendId });

    const handlePetUpdate = (payload: any) => {
        if (!payload) return;

        console.log(`[useFriendPetState] Received pet:state:${friendId}:`, payload);

        setData((prev: FriendPetData) => ({
            ...prev,
            pet: {
                name: payload.name || `Friend's Pet`,
                hunger: payload.hunger ?? 50,
                happiness: payload.happiness ?? 70,
                cleanliness: payload.cleanliness ?? 60,
                energy: payload.energy ?? 75,
                lastFed: payload.lastFed,
                lastPlayed: payload.lastPlayed,
                lastCleaned: payload.lastCleaned,
                lastSlept: payload.lastSlept,
                id: payload.id,
            },
        }));
    };

    console.log(`[useFriendPetState] Subscribing to pet:state:${friendId} (connected: ${isConnected})`);
    on(`pet:state:${friendId}`, handlePetUpdate);

    return () => {
        off(`pet:state:${friendId}`, handlePetUpdate as (...args: unknown[]) => void);
        emit('pet:unsubscribe', { userId: friendId });
    };
}, [friendId, isConnected, emit, on, off]);

  return data;
}
