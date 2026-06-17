// Pet State Interface
export interface PetState {
    id?: number;
    name: string;
    hunger: number; // 0 to 100
    happiness: number; // 0 to 100
    cleanliness: number; // 0 to 100
    energy: number; // 0 to 100
    lastFed?: string | null;
    lastPlayed?: string | null;
    lastCleaned?: string | null;
    lastSlept?: string | null;
}

// User Interface
export interface User {
    id: number;
    username: string;
    email: string;
    avatarUrl?: string;
}

export interface UserCustomization {
    cat: string;
    color: string;
    background: string;
}

export interface FriendPresence {
    id: number;
    username: string;
    email: string;
    avatarUrl?: string;
    isOnline: boolean;
}

// Chat Message Interface
export interface ChatMessage {
    id: number;
    userId: number;
    username: string;
    message: string;
    timestamp: Date;
}

// Action Types
export type PetAction = 'feed' | 'play' | 'clean' | 'sleep' | 'cuddle';
export type PetMood = 'happy' | 'idle' | 'sad' | 'eating' | 'sleepy' | 'asleep' | 'hungry'
    | 'dead' | 'dirty' | 'clean' | 'bored' | 'laughing' | 'shy' | 'no';
export type CatType = 'beigecat' | 'greycat' | 'orangecat' | 'whitecat';

// Auth Types

// Connected User
export interface AuthUser {
    id: number;
    username: string;
    email: string;
    avatarUrl?: string;
    catName?: string;
    customizations?: UserCustomization;
}

// What we send to backend for login
export interface LoginPayload {
    identifier: string;
    password: string;
}

// What we send to backend for registration
export interface RegisterPayload {
    username: string;
    email: string;
    password: string;
    avatar?: File | null;
    avatarUrl?: string;
    cat?: string;
    color?: string;
    background?: string;
}

export interface UpdateProfilePayload {
    newUsername?: string;
    newPassword?: string;
    newAvatarUrl?: string;
}

// What we receive from backend on successful login/registration
export interface AuthResponse {
    user?: AuthUser;
    newUser?: AuthUser | {
        id: number;
        username: string;
        email: string;
        cat?: string;
        color?: string;
        background?: string;
        avatarUrl?: string;
    };
    token?: string;
}

// ce qu'on recoit du backend quand la 2FA est demandee apres password login
export interface TwoFactorRequiredResponse {
    requires2FA: true;
    tempToken: string;
}

// ce qu'on envoie au backend pour finir un 2FA login
export interface TwoFactorVerifyPayload {
    tempToken: string;
    code: string;
}

// Auth Context State
export interface AuthState {
    user: AuthUser | null; // null when not authenticated
    token: string | null; // JWT token for authenticated requests
    isAuthenticated: boolean;
    loading: boolean;
    error: string | null;
}

export interface FriendRequest {
    id: number;
    fromUserId: number;
    toUserId: number;
    status: 'PENDING' | 'ACCEPTED' | 'REFUSED';
    fromUser?: User;
    toUser?: User;
}