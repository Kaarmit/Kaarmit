export interface PowerUp {
    id: string;
    name: string;
    icon: string;
    description: string;
    duration?: number;
    game: 'foodCatch' | 'race';
}

export interface Ability {
    id: string;
    name: string;
    icon: string;
    description: string;
    modifier: number;
    game: 'foodCatch' | 'race';
}

export const FOOD_CATCH_POWERUPS: PowerUp[] = [
    {
        id: 'magnetic',
        name: 'Magnetic Field',
        icon: '🧲',
        description: 'Attract all food items for 15 seconds',
        duration: 15,
        game: 'foodCatch',
    },
];

export const FOOD_CATCH_ABILITIES: Ability[] = [
    {
        id: 'happiness_boost',
        name: 'Happiness Boost',
        icon: '💛',
        description: '+2x happiness at the end',
        modifier: 2,
        game: 'foodCatch',
    },
];


export const DEFAULT_GAME_SETTINGS: Record<string, GameSettings> = {
    foodCatch: {
        powerUp: undefined,
        ability: FOOD_CATCH_ABILITIES[0],
        theme: 'Normal',
        difficulty: 'Normal',
    },
};


export interface GameSettings {
    powerUp?: PowerUp | undefined;
    ability?: Ability | undefined;
    theme?: string;
    difficulty?: 'Easy' | 'Normal' | 'Hard' | string;
}
