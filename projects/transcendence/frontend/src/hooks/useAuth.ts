// This hook manages authentication state and actions (login, logout, register) for the app. 
// It also integrates with the API service to handle token storage and automatic logout on 401 
// responses.
// The hook provides a simple interface for components to access the current user, authentication status,
// and perform authentication actions without needing to manage the underlying logic or API calls directly.

import { useState, useEffect, useCallback } from 'react';
import axios from 'axios';
import { api, setAuthFunctions } from '../services/api';
import socketService from '../services/socket';
import type { AuthUser, AuthState, LoginPayload, RegisterPayload, AuthResponse } from '../types';

const TOKEN_KEY = 'auth_token';
const USER_KEY = 'auth_user';
const DEFAULT_REGISTER_AVATARS = [
    '/avatar/beige.png',
    '/avatar/grey.png',
    '/avatar/orange.png',
    '/avatar/white.png',
] as const;

// types for pet profile response from backend (used to enrich AuthUser with pet data on login/registration)
type PetProfileResponse = {
    catName?: string | null;
    cat?: string | null;
    color?: string | null;
    background?: string | null;
};

// Function to convert the avatar to base64
const toBase64 = (file: File): Promise<string> =>
	new Promise((resolve, reject) => {
		const reader = new FileReader();
		reader.onload = () => resolve(reader.result as string);
		reader.onerror = reject;
		reader.readAsDataURL(file);
	});  

const getRandomDefaultRegisterAvatar = (): string => {
    const index = Math.floor(Math.random() * DEFAULT_REGISTER_AVATARS.length);
    return DEFAULT_REGISTER_AVATARS[index];
};

interface ApiErrorPayload {
    error?: string;
    message?: string;
    details?: {
        message?: string;
    };
}

const getApiErrorMessage = (error: unknown, fallback: string): string => {
    if (axios.isAxiosError(error)) {
        const status = error.response?.status;
        const data = error.response?.data as ApiErrorPayload | undefined;
        const serverMessage = data?.error ?? data?.message ?? data?.details?.message;

        if (status === 400) {
            return serverMessage ?? 'Invalid request data.';
        }

        if (status === 401) {
            return serverMessage ?? 'Invalid credentials.';
        }

        if (status === 403) {
            return serverMessage ?? 'You are not allowed to perform this action.';
        }

        if (status === 404) {
            return serverMessage ?? 'Resource not found.';
        }

        if (status === 409) {
            return serverMessage ?? 'Email or username is already taken.';
        }

        if (status === 422) {
            return serverMessage ?? 'Submitted data is not valid.';
        }

        if (status === 429) {
            return serverMessage ?? 'Too many requests. Please try again later.';
        }

        if (status === 500) {
            return serverMessage ?? 'Internal server error. Please try again later.';
        }

        if (status === 503) {
            return serverMessage ?? 'Service unavailable. Please try again later.';
        }

        if (serverMessage) {
            return serverMessage;
        }

        if (!error.response) {
            return 'Unable to reach the server.';
        }
    }

    return error instanceof Error ? error.message : fallback;
};

const getStoredToken = (): string | null => {
    try {
        return localStorage.getItem(TOKEN_KEY);
    } catch {
        return null;
    }
};

const getStoredUser = (): AuthUser | null => {
    try {
        const user = localStorage.getItem(USER_KEY);
        return user ? JSON.parse(user) : null;
    } catch {
        return null;
    }
};

const setStoredAuth = (token: string, user: AuthUser): void => {
    try {
        localStorage.setItem(TOKEN_KEY, token);
        localStorage.setItem(USER_KEY, JSON.stringify(user));
        window.dispatchEvent(new Event('auth-storage-changed'));
    } catch {
        console.error('Failed to store auth data');
    }
};

const clearStoredAuth = (): void => {
    try {
        localStorage.removeItem(TOKEN_KEY);
        localStorage.removeItem(USER_KEY);
        window.dispatchEvent(new Event('auth-storage-changed'));
    } catch {
        console.error('Failed to clear auth data');
    }
};

// Export token getter for api interceptor
export const getToken = getStoredToken;

// Export logout function for api interceptor (401 handling)
let logoutCallback: (() => void) | null = null;
export const setLogoutCallback = (callback: () => void) => {
    logoutCallback = callback;
};
export const triggerLogout = () => {
    if (logoutCallback) {
        logoutCallback();
    }
    clearStoredAuth();
};

// Fetch data pet profile from database
const fetchPetProfile = async (token: string): Promise<PetProfileResponse | null> => {
    try {
        const response = await api.get<PetProfileResponse>('/pets', {
            headers: {
                Authorization: `Bearer ${token}`,
            },
        });

        return response.data;
    } catch {
        return null;
    }
};

// Merge AuthUser with pet profile data (if available) to ensure we have the most up-to-date info on login/registration
const mergeAuthUserWithPetProfile = (user: AuthUser, petProfile: PetProfileResponse | null): AuthUser => ({
    ...user,
    catName: petProfile?.catName ?? user.catName,
    customizations: {
        cat: user.customizations?.cat ?? petProfile?.cat ?? 'beigecat',
        color: user.customizations?.color ?? petProfile?.color ?? '#FF69B4',
        background: user.customizations?.background ?? petProfile?.background ?? '/backgrounds/city.png',
    },
});

// Get the user object from the auth response
const getAuthUserFromResponse = (responseData: AuthResponse): AuthUser | null => (
    responseData.user ?? responseData.newUser ?? null
);

// Initialize API interceptors with auth functions
setAuthFunctions(getStoredToken, triggerLogout);

export const useAuth = () => {
    const [state, setState] = useState<AuthState>(() => {
        const token = getStoredToken();
        const user = getStoredUser();
        return {
            user,
            token,
            isAuthenticated: !!token && !!user,
            loading: !!token,
            error: null,
        };
    });

    // Register logout callback on mount
    // This ensures that if the token is invalidated and the API interceptor triggers a logout, our state will be updated accordingly.
    // We created user/me API route to validate the token on app load and fetch user data, so we can set loading to false after that check completes.
    // So we can show a loading state while we verify the token and fetch user data, preventing flashes of unauthenticated content if the token is valid.
    // Then if we have a token, we call the user/me endpoint to validate it and fetch the user data. If it's valid, we set loading to false and keep the user authenticated. 
    // If it's invalid, we clear the stored auth data and set the state to unauthenticated.
    useEffect(() => {
        const token = getStoredToken();
        if (!token) return;
        api.get('/users/me')
            .then(() => {
                socketService.connect(token);
                setState(prev => ({ ...prev, loading: false }));
            })
            .catch(() => {
                clearStoredAuth();
                setState({ user: null, token: null, isAuthenticated: false, loading: false, error: null });
            });
    }, []);

    // Register logout callback on mount
    useEffect(() => {
        setLogoutCallback(() => {
            setState({ user: null, token: null, isAuthenticated: false, loading: false, error: null });
        });
        return () => { setLogoutCallback(() => { }); };
    }, []);

    const login = useCallback(async (payload: LoginPayload): Promise<boolean> => {
        setState(prev => ({ ...prev, loading: true, error: null }));
        const trimmedIdentifier = payload.identifier.trim();
        const isEmail = trimmedIdentifier.includes('@');
        const loginRequestBody = isEmail
            ? { email: trimmedIdentifier, password: payload.password }
            : { username: trimmedIdentifier, password: payload.password };

        try {
            // API call - will work with real backend
            const response = await api.post<AuthResponse>('/auth/login', loginRequestBody);
            const { token } = response.data;
            let user = getAuthUserFromResponse(response.data);

            if (!user) {
                throw new Error('Login response did not include a user');
            }

            // Normalize into `user.customizations` like we do on register
            if (!user.customizations) {
                user = {
                    ...user,
                    customizations: {
                        cat: (user as any).cat ?? 'beigecat',
                        color: (user as any).color ?? '#FF69B4',
                        background: (user as any).background ?? '/backgrounds/city.png',
                    }
                };
            }

            const petProfile = await fetchPetProfile(token);
            const userWithPetProfile = mergeAuthUserWithPetProfile(user, petProfile);

            setStoredAuth(token, userWithPetProfile);
            socketService.connect(token);
            setState({
                user: userWithPetProfile,
                token,
                isAuthenticated: true,
                loading: false,
                error: null,
            });

            return true;
        } catch (error: unknown) {
            const message = getApiErrorMessage(error, 'Login failed');
            setState(prev => ({
                ...prev,
                loading: false,
                error: message,
            }));
            return false;
        }
    }, []);

    const register = useCallback(async (payload: RegisterPayload): Promise<boolean> => {
        setState(prev => ({ ...prev, loading: true, error: null }));
        const fallbackAvatarUrl = payload.avatarUrl || getRandomDefaultRegisterAvatar();

        try {
			const avatarUrl = payload.avatar instanceof File
				? await toBase64(payload.avatar)
				: fallbackAvatarUrl;

            const requestBody = {
                username: payload.username,
                email: payload.email,
                password: payload.password,
                avatarUrl,
                cat: payload.cat,
                color: payload.color,
                background: payload.background,
            };
			
			const response = await api.post<AuthResponse>('/auth/register', requestBody);

            const { token } = response.data;
            let user = getAuthUserFromResponse(response.data);

            if (!user) {
                throw new Error('Registration response did not include a user');
            }

            // Backend returns newUser with flat customization fields, so structure them into customizations object
            if (!user.customizations) {
                user = {
                    ...user,
                    customizations: {
                        cat: (user as any).cat ?? 'beigecat',
                        color: (user as any).color ?? '#FF69B4',
                        background: (user as any).background ?? '/backgrounds/city.png',
                    }
                };
            }

            const petProfile = await fetchPetProfile(token);
            const userWithPetProfile = mergeAuthUserWithPetProfile(user, petProfile);

            setStoredAuth(token, userWithPetProfile);
            setState({
                user: userWithPetProfile,
                token,
                isAuthenticated: true,
                loading: false,
                error: null,
            });

            return true;
        } catch (error: unknown) {
            const message = getApiErrorMessage(error, 'Registration failed');
            setState(prev => ({
                ...prev,
                loading: false,
                error: message,
            }));
            return false;
        }
    }, []);

    const logout = useCallback(async () => {
        socketService.disconnect();
        
        // Dispatch event to PetContext to save pet state BEFORE clearing auth
        window.dispatchEvent(new Event('before-logout'));
        
        // Wait a bit to allow pet state save to complete
        await new Promise(resolve => setTimeout(resolve, 500));
        
        clearStoredAuth();
        setState({
            user: null,
            token: null,
            isAuthenticated: false,
            loading: false,
            error: null,
        });
    }, []);

    const clearError = useCallback(() => {
        setState(prev => ({ ...prev, error: null }));
    }, []);

    const refreshUser = useCallback(async (): Promise<boolean> => {
        try {
            const response = await api.get('/users/me');
            const updatedUser = response.data.user as AuthUser;
            
            const token = getStoredToken();
            if (token) {
                setStoredAuth(token, updatedUser);
                setState(prev => ({
                    ...prev,
                    user: updatedUser,
                }));
                return true;
            }
            return false;
        } catch {
            return false;
        }
    }, []);

    return {
        user: state.user,
        token: state.token,
        isAuthenticated: state.isAuthenticated,
        loading: state.loading,
        error: state.error,
        login,
        logout,
        register,
        clearError,
        refreshUser,
    };
};

export default useAuth;
