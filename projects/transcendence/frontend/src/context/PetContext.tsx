import { createContext, useContext, useState, useEffect, useRef, useCallback, type ReactNode } from 'react';
import type { AuthUser, PetState, PetAction, PetMood, CatType, UserCustomization } from '../types';
import { petAPI } from '../services/api';
import { useSocket } from '../hooks/useSocket';
import { useAuth } from '../hooks/useAuth';

interface PetContextType {
    pet: PetState;
    mood: PetMood;
    performAction: (action: PetAction) => void;
    addHappiness: (amount: number) => void;
    addHunger: (amount: number) => void;
    setPetName: (name: string) => void;
    color: string;
    setColor: (color: string) => void;
    selectedBackground: string;
    setSelectedBackground: (background: string) => void;
    catType: CatType;
    setCatType: (catType: CatType) => void;
    resetToDefaults: () => void;
}

const PetContext = createContext<PetContextType | null>(null);

const AUTH_USER_KEY = 'auth_user';
const PET_STATE_KEY = 'petState';
const PET_COLOR_KEY = 'petColor';
const PET_BACKGROUND_KEY = 'selectedBackground';
const PET_CAT_TYPE_KEY = 'catType';

export const DEFAULT_PET_STATE: PetState = {
    id: 1,
    name: 'Fluffy',
    hunger: 75,
    happiness: 80,
    cleanliness: 85,
    energy: 90,
    lastFed: new Date(Date.now() - 3600000).toISOString(),
    lastPlayed: new Date(Date.now() - 7200000).toISOString(),
    lastCleaned: new Date(Date.now() - 10800000).toISOString(),
};

export const DEFAULT_PET_COLOR = '#FF69B4';
export const DEFAULT_PET_BACKGROUND = '/backgrounds/city.png';
export const DEFAULT_CAT_TYPE: CatType = 'beigecat';

const getCurrentUserId = (): number | null => {
    try {
        const rawUser = localStorage.getItem(AUTH_USER_KEY);
        if (!rawUser) {
            return null;
        }

        const parsedUser = JSON.parse(rawUser) as { id?: number };
        return typeof parsedUser.id === 'number' ? parsedUser.id : null;
    } catch {
        return null;
    }
};

const getStoredAuthUser = (): AuthUser | null => {
    try {
        const rawUser = localStorage.getItem(AUTH_USER_KEY);
        if (!rawUser) {
            return null;
        }

        return JSON.parse(rawUser) as AuthUser;
    } catch {
        return null;
    }
};

const getStoredAuthUserCatName = (): string | null => {
    const storedAuthUser = getStoredAuthUser();
    return typeof storedAuthUser?.catName === 'string' && storedAuthUser.catName.trim()
        ? storedAuthUser.catName
        : null;
};

const getStoredAuthUserCustomizations = (): UserCustomization | null => {
    const storedAuthUser = getStoredAuthUser();
    return storedAuthUser?.customizations ?? null;
};

const getScopedStorageKey = (key: string, userId: number | null): string => (
    userId === null ? key : `${key}:${userId}`
);

const parseStoredPetState = (rawValue: string | null): PetState | null => {
    if (!rawValue) {
        return null;
    }

    try {
        return JSON.parse(rawValue) as PetState;
    } catch {
        return null;
    }
};

const loadPetState = (userId: number | null): PetState => {
    const scopedKey = getScopedStorageKey(PET_STATE_KEY, userId);

    const scopedState = parseStoredPetState(localStorage.getItem(scopedKey));
    if (scopedState) {
        return scopedState;
    }

    const catName = getStoredAuthUserCatName();
    if (catName) {
        return {
            ...DEFAULT_PET_STATE,
            name: catName,
        };
    }

    return DEFAULT_PET_STATE;
};

const loadPetColor = (userId: number | null): string => {
    const scopedKey = getScopedStorageKey(PET_COLOR_KEY, userId);
    const scopedColor = localStorage.getItem(scopedKey);
    const customizations = getStoredAuthUserCustomizations();
    if (customizations?.color) {
        return customizations.color;
    }

    if (scopedColor) {
        return scopedColor;
    }

    return DEFAULT_PET_COLOR;
};

const loadSelectedBackground = (userId: number | null): string => {
    const scopedKey = getScopedStorageKey(PET_BACKGROUND_KEY, userId);
    const scopedBackground = localStorage.getItem(scopedKey);
    const customizations = getStoredAuthUserCustomizations();
    if (customizations?.background) {
        return customizations.background;
    }

    if (scopedBackground) {
        return scopedBackground;
    }

    return DEFAULT_PET_BACKGROUND;
};

const loadCatType = (userId: number | null): CatType => {
    const scopedKey = getScopedStorageKey(PET_CAT_TYPE_KEY, userId);
    const scopedCatType = localStorage.getItem(scopedKey);
    const value = scopedCatType;
    const customizations = getStoredAuthUserCustomizations();
    if (
        customizations?.cat === 'beigecat' ||
        customizations?.cat === 'greycat' ||
        customizations?.cat === 'orangecat' ||
        customizations?.cat === 'whitecat'
    ) {
        return customizations.cat;
    }

    if (
        value === 'beigecat' ||
        value === 'greycat' ||
        value === 'orangecat' ||
        value === 'whitecat'
    ) {
        return value;
    }

    return DEFAULT_CAT_TYPE;
};

export function PetProvider({ children }: { children: ReactNode }) {
    const [storageUserId, setStorageUserId] = useState<number | null>(() => getCurrentUserId());
    const [pet, setPet] = useState<PetState>(() => loadPetState(getCurrentUserId()));
    const [mood, setMood] = useState<PetMood>('idle');
    const [color, setColor] = useState<string>(() => loadPetColor(getCurrentUserId()));
    const [selectedBackground, setSelectedBackground] = useState<string>(() => loadSelectedBackground(getCurrentUserId()));
    const [catType, setCatType] = useState<CatType>(() => loadCatType(getCurrentUserId()));
    const moodTimeoutRef = useRef<ReturnType<typeof setTimeout> | null>(null);
    const sleepyTimeoutRef = useRef<ReturnType<typeof setTimeout> | null>(null);
    const isAnimatingRef = useRef<boolean>(false);
    const petRef = useRef<PetState>(pet);
    const prevEnergyRef = useRef<number>(pet.energy);
    const prevUserIdRef = useRef<number | null>(getCurrentUserId());

	const { token } = useAuth();
	const { emit, isConnected } = useSocket({ autoConnect: !!token, token: token ?? undefined });

    useEffect(() => {
        petRef.current = pet;
    }, [pet]);

    const resetToDefaults = useCallback(() => {
        setPet(DEFAULT_PET_STATE);
        setMood('idle');
        setColor(DEFAULT_PET_COLOR);
        setSelectedBackground(DEFAULT_PET_BACKGROUND);
        setCatType(DEFAULT_CAT_TYPE);
        prevEnergyRef.current = DEFAULT_PET_STATE.energy;
    }, []);

    useEffect(() => {
        const refreshUserStorageScope = () => {
            setStorageUserId(getCurrentUserId());
        };

        window.addEventListener('storage', refreshUserStorageScope);
        window.addEventListener('auth-storage-changed', refreshUserStorageScope);

        return () => {
            window.removeEventListener('storage', refreshUserStorageScope);
            window.removeEventListener('auth-storage-changed', refreshUserStorageScope);
        };
    }, []);

    // Load pet state from server on app startup
    useEffect(() => {
        const loadFromServer = async () => {
            if (storageUserId === null) return;
            
            try {
                const response = await petAPI.getPetState();
                if (response.data) {
                    setPet(response.data);
                    // Customizations (color, background, cat) come from AuthUser, not from pet state
                    const color = loadPetColor(storageUserId);
                    const bg = loadSelectedBackground(storageUserId);
                    const cat = loadCatType(storageUserId);
                    setColor(color);
                    setSelectedBackground(bg);
                    setCatType(cat);
                    localStorage.setItem(
                        getScopedStorageKey(PET_STATE_KEY, storageUserId),
                        JSON.stringify(response.data)
                    );
                }
            } catch (error) {
                console.warn('Failed to load pet state from server, using local data:', error);
                const nextPetState = loadPetState(storageUserId);
                const color = loadPetColor(storageUserId);
                const bg = loadSelectedBackground(storageUserId);
                const cat = loadCatType(storageUserId);
                setPet(nextPetState);
                setColor(color);
                setSelectedBackground(bg);
                setCatType(cat);
                prevEnergyRef.current = nextPetState.energy;
            }
        };

        // Only load from server if user is authenticated
        if (storageUserId !== null) {
            loadFromServer();
        } else {
            setPet(DEFAULT_PET_STATE);
            setColor(DEFAULT_PET_COLOR);
            setSelectedBackground(DEFAULT_PET_BACKGROUND);
            setCatType(DEFAULT_CAT_TYPE);
            prevEnergyRef.current = DEFAULT_PET_STATE.energy;
        }
    }, [storageUserId]);

    useEffect(() => {
        const handleBeforeLogout = () => {
            // Save pet state to server before logout completes
            if (storageUserId !== null) {
                petAPI.updatePetState(petRef.current).catch(error => {
                    console.warn('[Pet] Failed to save state before logout:', error);
                });
            }
        };

        window.addEventListener('before-logout', handleBeforeLogout);
        return () => {
            window.removeEventListener('before-logout', handleBeforeLogout);
        };
    }, [storageUserId]);

    useEffect(() => {
        // Detect logout (userId changed from non-null to null)
        const previousUserId = prevUserIdRef.current;
        const currentUserId = storageUserId;

        if (previousUserId !== null && currentUserId === null) {
            // User just logged out - clear localStorage scoped keys
            localStorage.removeItem(getScopedStorageKey(PET_STATE_KEY, previousUserId));
            localStorage.removeItem(getScopedStorageKey(PET_COLOR_KEY, previousUserId));
            localStorage.removeItem(getScopedStorageKey(PET_BACKGROUND_KEY, previousUserId));
            localStorage.removeItem(getScopedStorageKey(PET_CAT_TYPE_KEY, previousUserId));
        }

        prevUserIdRef.current = currentUserId;
    }, [storageUserId]);

    useEffect(() => {
        localStorage.setItem(getScopedStorageKey(PET_CAT_TYPE_KEY, storageUserId), catType);
    }, [catType, storageUserId]);

    useEffect(() => {
        const pawByCatType: Record<CatType, string> = {
            beigecat: '/paw/cursor/beige.png',
            greycat: '/paw/cursor/grey.png',
            orangecat: '/paw/cursor/orange.png',
            whitecat: '/paw/cursor/white.png',
        };

        document.documentElement.style.setProperty(
            '--paw-cursor',
            `url('${pawByCatType[catType]}') 8 8`
        );
    }, [catType]);

    useEffect(() => {
        const prevEnergy = prevEnergyRef.current;
        const currentEnergy = pet.energy;

        if (prevEnergy > 50 && currentEnergy <= 50 && !isAnimatingRef.current) {
            if (sleepyTimeoutRef.current) {
                clearTimeout(sleepyTimeoutRef.current);
            }

            setMood('sleepy');
            isAnimatingRef.current = true;

            sleepyTimeoutRef.current = setTimeout(() => {
                isAnimatingRef.current = false;
                setPet(prev => {
                    setMood(calculateMood(prev));
                    return prev;
                });
            }, 10000);
        }

        prevEnergyRef.current = currentEnergy;
    }, [pet.energy]);

    // Automatic decay - each stat with its own interval
    useEffect(() => {
        const hungerInterval = setInterval(() => {
            setPet(prev => ({
                ...prev,
                hunger: Math.max(0, prev.hunger - 1),
            }));
        }, 5000);

        const happinessInterval = setInterval(() => {
            setPet(prev => ({
                ...prev,
                happiness: Math.max(0, prev.happiness - 1),
            }));
        }, 5000);

        const cleanlinessInterval = setInterval(() => {
            setPet(prev => ({
                ...prev,
                cleanliness: Math.max(0, prev.cleanliness - 1),
            }));
        }, 10000);

        const energyInterval = setInterval(() => {
            setPet(prev => ({
                ...prev,
                energy: Math.max(0, prev.energy - 1),
            }));
        }, 5000);

        return () => {
            clearInterval(hungerInterval);
            clearInterval(happinessInterval);
            clearInterval(cleanlinessInterval);
            clearInterval(energyInterval);
        };
    }, []);

    const calculateMood = (petState: PetState): PetMood => {
        if (petState.hunger === 0 && petState.happiness === 0 && petState.cleanliness === 0 && petState.energy === 0) {
            return 'dead';
        }
        if (petState.happiness < 20) {
            return 'sad';
        }
        const negatives = [
            petState.hunger < 30,
            petState.happiness < 20,
            petState.cleanliness < 10,
            petState.energy < 20,
        ];
        if (negatives.filter(Boolean).length >= 3) {
            return 'sad';
        }
        if (petState.hunger < 30) {
            return 'hungry';
        }
        if (petState.cleanliness < 10) {
            return 'dirty';
        }
        if (petState.energy < 50) {
            return 'sleepy';
        }
        if (petState.hunger >= 90 && petState.happiness >= 90 && petState.cleanliness >= 90 && petState.energy >= 60) {
            return 'happy';
        }
        return 'idle';
    };

    useEffect(() => {
        if (!isAnimatingRef.current) {
            setMood(calculateMood(pet));
        }
    }, [pet.hunger, pet.happiness, pet.cleanliness, pet.energy]);

    const performAction = (action: PetAction) => {
        const actionTargetStat: Record<PetAction, keyof Pick<PetState, 'hunger' | 'happiness' | 'cleanliness' | 'energy'>> = {
            feed: 'hunger',
            play: 'happiness',
            cuddle: 'happiness',
            clean: 'cleanliness',
            sleep: 'energy',
        };

        const targetStat = actionTargetStat[action];
        if (pet[targetStat] >= 100) {
            if (moodTimeoutRef.current) {
                clearTimeout(moodTimeoutRef.current);
            }
            setMood('no');
            moodTimeoutRef.current = setTimeout(() => {
                setPet(prev => {
                    setMood(calculateMood(prev));
                    return prev;
                });
            }, 10000);
            return;
        }

        if (moodTimeoutRef.current) {
            clearTimeout(moodTimeoutRef.current);
        }
        isAnimatingRef.current = true;

        // Progressive stat increase config
        const progressiveConfigs: Record<PetAction, { stat: keyof PetState; total: number; interval: number; lastKey: keyof PetState }> = {
            feed: { stat: 'hunger', total: 25, interval: 200, lastKey: 'lastFed' },
            clean: { stat: 'cleanliness', total: 20, interval: 250, lastKey: 'lastCleaned' },
            sleep: { stat: 'energy', total: 20, interval: 300, lastKey: 'lastSlept' },
            play: { stat: 'happiness', total: 10, interval: 500, lastKey: 'lastPlayed' },
            cuddle: { stat: 'happiness', total: 15, interval: 200, lastKey: 'lastPlayed' },
        };

        const config = progressiveConfigs[action];
        let remaining = config.total;

        // Update lastX timestamp immediately
        setPet(prev => ({
            ...prev,
            [config.lastKey]: new Date().toISOString(),
        }));

        // Progressive increase
        const intervalId = setInterval(() => {
            if (remaining > 0) {
                setPet(prev => ({
                    ...prev,
                    [config.stat]: Math.min(100, (prev[config.stat] as number) + 1),
                }));
                remaining--;
            } else {
                clearInterval(intervalId);
            }
        }, config.interval);

        const actionMoods: Record<PetAction, PetMood> = {
            feed: 'eating',
            play: 'happy',
            clean: 'clean',
            sleep: 'asleep',
            cuddle: 'shy',
        };
        setMood(actionMoods[action]);

        const animationDuration = config.total * config.interval;

        moodTimeoutRef.current = setTimeout(() => {
            clearInterval(intervalId);
            isAnimatingRef.current = false;
            setPet(prev => {
                setMood(calculateMood(prev));
                return prev;
            });
        }, animationDuration + 500);

        setTimeout(() => {
            setPet(prev => {
                localStorage.setItem(getScopedStorageKey(PET_STATE_KEY, storageUserId), JSON.stringify(prev));
                return prev;
            });
        }, 1000);
    };

    // Add happiness from mini-games
    const addHappiness = useCallback((amount: number) => {
        setPet(prev => {
            const newState = {
                ...prev,
                happiness: Math.min(100, prev.happiness + amount),
                lastPlayed: new Date().toISOString(),
            };
            localStorage.setItem(getScopedStorageKey(PET_STATE_KEY, storageUserId), JSON.stringify(newState));
            return newState;
        });
    }, [storageUserId]);

    const addHunger = useCallback((amount: number) => {
        setPet(prev => {
            const newState = {
                ...prev,
                hunger: Math.min(100, prev.hunger + amount),
                lastFed: new Date().toISOString(),
            };
            localStorage.setItem(getScopedStorageKey(PET_STATE_KEY, storageUserId), JSON.stringify(newState));
            return newState;
        });
    }, [storageUserId]);

    const setPetName = useCallback((name: string) => {
        setPet(prev => {
            const newState = {
                ...prev,
                name,
            };
            localStorage.setItem(getScopedStorageKey(PET_STATE_KEY, storageUserId), JSON.stringify(newState));
            return newState;
        });
    }, [storageUserId]);

    // Auto-save pet state whenever it changes (only when user is logged in)
    useEffect(() => {
        if (storageUserId !== null) {
            localStorage.setItem(getScopedStorageKey(PET_STATE_KEY, storageUserId), JSON.stringify(pet));
        }
    }, [pet, storageUserId]);

    // Persist pet state periodically so viewers receive the backend broadcast from PUT /pets/state
    useEffect(() => {
        if (!storageUserId || !isConnected) return;
		console.log('[PetContext] emitting pet:state:update, connected:',
			isConnected);

        emit('pet:state:update', {
            userId: storageUserId,
            petState: petRef.current,
        });

        const emitInterval = setInterval(() => {
            emit('pet:state:update', {
                userId: storageUserId,
                petState: petRef.current,
            });
        }, 7000);

        return () => clearInterval(emitInterval);
    }, [storageUserId, isConnected, emit]);

    useEffect(() => {
        localStorage.setItem(getScopedStorageKey(PET_COLOR_KEY, storageUserId), color);
    }, [color, storageUserId]);

    useEffect(() => {
        localStorage.setItem(getScopedStorageKey(PET_BACKGROUND_KEY, storageUserId), selectedBackground);
    }, [selectedBackground, storageUserId]);

    useEffect(() => {
        return () => {
            if (moodTimeoutRef.current) {
                clearTimeout(moodTimeoutRef.current);
            }
        };
    }, []);

    return (
        <PetContext.Provider value={{ pet, mood, performAction, addHappiness, addHunger, setPetName, color, setColor, selectedBackground, setSelectedBackground, catType, setCatType, resetToDefaults }}>
            {children}
        </PetContext.Provider>
    );
}

export function usePet() {
    const context = useContext(PetContext);
    if (!context) {
        throw new Error('usePet must be used within a PetProvider');
    }
    return context;
}
