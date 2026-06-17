export interface AuthUser {
    id: number;
    username: string;
    email: string;
    avatarUrl?: string;
}

export interface AuthResponse {
    user: AuthUser;
    token: string;
}