import { useState, useEffect, useCallback, useRef, type PointerEvent } from 'react';
import { useNavigate } from 'react-router-dom';
import { usePet } from '../../context/PetContext';
import styled from 'styled-components';
import 'three';

interface FoodItem {
    id: number;
    x: number;
    y: number;
    emoji: string;
    points: number;
    speed: number;
    pickup?: 'magnetic' | 'happiness';
}

interface Player {
    x: number;
    width: number;
}

const FOOD_EMOJIS = [
    { emoji: '🍱', points: 2 },
    { emoji: '🍖', points: 2 },
    { emoji: '🌮', points: 2 },
    { emoji: '🍔', points: 1 },
    { emoji: '🧋', points: 1 },
    { emoji: '🍛', points: 1 },
    { emoji: '🍧', points: 0 },
    { emoji: '🥦', points: -1 },
    { emoji: '🥗', points: -2 },
    { emoji: '🧲', points: 0, pickup: 'magnetic' },
    { emoji: '💛', points: 0, pickup: 'happiness' },
];

const GAME_WIDTH = 800;
const GAME_HEIGHT = 450;
const PLAYER_WIDTH = 80;
const GAME_DURATION = 30;
const HUMAN_BOTTOM = 10;
const AI_BOTTOM = HUMAN_BOTTOM;
const HUMAN_COLLISION_MIN_Y = GAME_HEIGHT - 60;
const HUMAN_COLLISION_MAX_Y = GAME_HEIGHT - 20;
const AI_COLLISION_MIN_Y = GAME_HEIGHT - 60;
const AI_COLLISION_MAX_Y = GAME_HEIGHT - 20;

const GameContainer = styled.div`
  width: 100%;
  min-height: 100vh;
  position: relative;
  overflow: hidden;
`;

const CanvasBackground = styled.div`
  position: absolute;
  inset: 0;
  z-index: 0;
`;

const StyledCanvasWrapper = styled.div`
  height: 100vh;
  background: radial-gradient(circle, #2a1a4e 0%, #0a0a1e 100%);
`;

const GameContent = styled.div`
  position: relative;
  z-index: 1;
  height: 100%;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 20px;
`;

const Header = styled.div`
  display: flex;
  justify-content: space-between;
  width: 100%;
  max-width: ${GAME_WIDTH}px;
  flex-wrap: wrap;
  gap: 15px;
  margin-bottom: 20px;
  color: white;
`;

const HeaderRow = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  width: 100%;
  gap: 15px;
`;

const HeaderTimerRow = styled.div`
  display: flex;
  justify-content: center;
  width: 100%;
`;

const HeaderBoxCenter = styled.div`
  flex: 1;
  text-align: center;
  background: rgba(0, 0, 0, 0.5);
  padding: 14px 20px;
  border-radius: 20px;
  font-size: 1rem;
`;

const HeaderBox = styled.div<{ isTimer?: boolean; danger?: boolean }>`
  background: rgba(0, 0, 0, 0.5);
  padding: 14px 20px;
  border-radius: 20px;
  font-size: 1rem;

  ${props => props.isTimer && `
    min-width: 170px;
    max-width: 50%;
    color: white;
  `}

  ${props => props.danger ? `
    color: #a05d5d;
    animation: dangerBlink 0.8s step-end infinite;
    
    @keyframes dangerBlink {
      0%, 49%, 100% { opacity: 1; }
      50%, 99% { opacity: 0.5; }
    }
  ` : ''}
`;

const HeaderLabel = styled.div<{ color?: string }>`
  color: ${props => props.color || '#fbbf24'};
  font-size: 0.9rem;
  margin-bottom: 2px;
`;

const HeaderValue = styled.div`
  font-weight: bold;
`;

const GameAreaWrapper = styled.div<{ gameScale?: number }>`
  width: ${props => GAME_WIDTH * (props.gameScale || 1)}px;
  max-width: 100%;
  height: ${props => GAME_HEIGHT * (props.gameScale || 1)}px;
  border-radius: 20px;
  border: 3px solid rgba(102, 126, 234, 0.5);
  position: relative;
  overflow: hidden;
  cursor: pointer;
  touch-action: none;
  
  &[data-playing='true'] {
    cursor: none;
  }
`;

const GameBackground = styled.div<{ gameScale?: number }>`
  width: ${GAME_WIDTH}px;
  height: ${GAME_HEIGHT}px;
  background-image: url(/game/foodcatchbackground.jpg);
  background-size: 100% 100%;
  background-position: center;
  background-repeat: no-repeat;
  background-color: rgba(0, 0, 0, 0.6);
  position: relative;
  transform: ${props => `scale(${props.gameScale || 1})`};
  transform-origin: top left;
`;

const FoodEmoji = styled.div`
  position: absolute;
  left: 0;
  top: 0;
  font-size: 2rem;
  transition: none;
  pointer-events: none;
  will-change: transform;
`;

const PlayerContainer = styled.div<{ playerScale?: number; isAI?: boolean }>`
  position: absolute;
  width: ${PLAYER_WIDTH}px;
  height: 60px;
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: ${props => props.isAI ? 0.88 : 1};
  filter: ${props => props.playerScale && props.playerScale > 1
    ? 'drop-shadow(0 0 20px #FFD700) brightness(1.3)'
    : props.isAI
      ? 'drop-shadow(0 0 12px rgba(96, 165, 250, 0.75)) hue-rotate(120deg)'
      : 'drop-shadow(0 4px 8px rgba(0, 0, 0, 0.4))'};
  transform: ${props => `scale(${props.playerScale || 1})`};
  transform-origin: center bottom;
  transition: transform 0.1s, filter 0.1s;
`;

const PlayerImage = styled.img`
  width: 56px;
  height: 56px;
  object-fit: contain;
  image-rendering: pixelated;
  user-select: none;
  pointer-events: none;
`;

const AiNameTag = styled.div`
  position: absolute;
  bottom: -15px;
  color: #60a5fa;
  font-size: 11px;
  font-weight: bold;
  text-shadow: 1px 1px 2px black;
`;

const OverlayScreen = styled.div`
  position: absolute;
  inset: 0;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  background: rgba(0, 0, 0, 0.7);
  padding: 20px;
`;

const WaitingScreenContent = styled(OverlayScreen)`
  background: rgba(0, 0, 0, 0.7);
`;

const FinishedScreenContent = styled.div`
  position: absolute;
  inset: 0;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  background: rgba(0, 0, 0, 0.85);
  padding: 12px;
  box-sizing: border-box;
  width: 100%;
  max-width: 100%;
  overflow-y: auto;
  -webkit-overflow-scrolling: touch;
`;

const FinishedContainer = styled.div`
  width: 100%;
  max-width: 390px;
  text-align: center;
`;

const ScreenTitle = styled.h2`
  color: white;
  font-size: clamp(1.5rem, 4vw, 2rem);
  margin: 0;
  line-height: 1.2;
`;

const ScreenSubtitle = styled.p`
  color: rgba(255, 255, 255, 0.7);
  margin-top: 10px;
  font-size: clamp(0.9rem, 2.2vw, 1rem);
`;

const ScreenInstruction = styled.p`
  color: rgba(255, 255, 255, 0.5);
  font-size: clamp(0.8rem, 1.9vw, 0.9rem);
`;

const ScoreDisplay = styled.div`
  margin-top: 10px;
  font-size: clamp(1.2rem, 4vw, 1.8rem);
  color: #bb2e8c;
  text-shadow: 0 0 18px rgba(255, 215, 0, 0.5);
`;

const RewardMessage = styled.div`
  margin-top: 10px;
  padding: 12px 14px;
  background: rgba(119, 75, 119, 0.3);
  border-radius: 15px;
  color: #a197a0;
  font-size: clamp(0.75rem, 1.8vw, 0.95rem);
  text-align: center;
  word-break: break-word;
`;

const ResultMessage = styled.div<{ won?: boolean }>`
  margin-top: 10px;
  padding: 12px 14px;
  background: ${props => props.won ? 'rgba(74, 222, 128, 0.22)' : 'rgba(248, 113, 113, 0.22)'};
  border-radius: 15px;
  color: ${props => props.won ? '#86efac' : '#fca5a5'};
  font-size: clamp(0.8rem, 1.9vw, 1rem);
  font-weight: bold;
  text-align: center;
`;

const ButtonGroup = styled.div`
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  gap: 12px;
  margin-top: 16px;
`;

const PrimaryButton = styled.button`
  padding: 16px 48px;
  font-size: clamp(1rem, 2.5vw, 1.2rem);
  font-weight: bold;
  background: linear-gradient(135deg, #aa82dd 0%, #f05ebf 100%);
  border: none;
  border-radius: 50px;
  color: white;
  cursor: pointer;
  box-shadow: 0 8px 32px rgba(255, 107, 107, 0.4);
  transition: transform 0.2s;

  &:hover {
    transform: scale(1.05);
  }
`;

const SecondaryButton = styled.button`
  padding: 14px 32px;
  font-size: clamp(0.95rem, 2.2vw, 1rem);
  font-weight: bold;
  background: linear-gradient(135deg, #b9b9b9 0%, #e484d7 100%);
  border: none;
  border-radius: 50px;
  color: white;
  cursor: pointer;
  transition: transform 0.2s;

  &:hover {
    transform: scale(1.05);
  }
`;

const BackButton = styled.button`
  margin-top: 20px;
  padding: 10px 20px;
  background: transparent;
  border: 2px solid #6b7280;
  border-radius: 10px;
  color: #9ca3af;
  cursor: pointer;
`;

const ReturnButton = styled.button`
  margin-top: 20px;
  padding: 12px 30px;
  font-size: 1rem;
  background: rgba(255, 255, 255, 0.1);
  border: 2px solid rgba(255, 255, 255, 0.3);
  border-radius: 50px;
  color: white;
  cursor: pointer;
  transition: all 0.3s ease;
  backdrop-filter: blur(10px);

  &:hover {
    background: rgba(255, 255, 255, 0.2);
  }
`;

const getPlayerCatKey = (selectedCatType: string) => {
    if (selectedCatType === 'greycat') return 'grey';
    if (selectedCatType === 'orangecat') return 'orange';
    if (selectedCatType === 'whitecat') return 'white';
    return 'beige';
};

const getAiCatKey = (selectedCatType: string) => {
    if (selectedCatType === 'greycat') return 'orange';
    return 'grey';
};

export default function FoodCatchGame() {
    const navigate = useNavigate();
    const { pet, addHappiness, addHunger, catType } = usePet();
    const gameRef = useRef<HTMLDivElement>(null);
    const animationRef = useRef<number | null>(null);
    const pointerFrameRef = useRef<number | null>(null);
    const lastSpawnRef = useRef<number>(0);
    const addHappinessRef = useRef(addHappiness);
    const happinessAddedRef = useRef(false);
    const addHungerRef = useRef(addHunger);
    const hungerAddedRef = useRef(false);
    const catchTimeoutRef = useRef<ReturnType<typeof setTimeout> | null>(null);
    const aiCatchTimeoutRef = useRef<ReturnType<typeof setTimeout> | null>(null);
    const pickupCountsRef = useRef({ magnetic: 0, happiness: 0 });
    const playerRef = useRef<Player>({ x: GAME_WIDTH / 2 - PLAYER_WIDTH / 2, width: PLAYER_WIDTH });
    const aiPlayerRef = useRef<Player>({ x: GAME_WIDTH / 2 + 120, width: PLAYER_WIDTH });

    const [gameState, setGameState] = useState<'waiting' | 'playing' | 'finished'>('waiting');
    const [timeLeft, setTimeLeft] = useState(GAME_DURATION);
    const [foods, setFoods] = useState<FoodItem[]>([]);
    const [player, setPlayer] = useState<Player>({ x: GAME_WIDTH / 2 - PLAYER_WIDTH / 2, width: PLAYER_WIDTH });
    const [aiPlayer, setAiPlayer] = useState<Player>({ x: GAME_WIDTH / 2 + 120, width: PLAYER_WIDTH });
    const [aiEnabled, setAiEnabled] = useState(false);
    const [happinessGained, setHappinessGained] = useState(0);
    const [hungerLost, setHungerLost] = useState(0);
    const [hungerPoints, setHungerPoints] = useState(0);
    const [happinessPoints, setHappinessPoints] = useState(0);
    const [aiScore, setAiScore] = useState(0);
    const [isCatching, setIsCatching] = useState(false);
    const [isAiCatching, setIsAiCatching] = useState(false);
    const [gameScale, setGameScale] = useState(1);
    const [magneticActive, setMagneticActive] = useState(false);
    const [happinessMultiplier, setHappinessMultiplier] = useState(1);

    const playerCatKey = getPlayerCatKey(catType);
    const aiCatKey = getAiCatKey(catType);
    const playerSpriteIdle = `/food/${playerCatKey}o.png`;
    const playerSpriteCatch = `/food/${playerCatKey}m.png`;
    const aiSpriteIdle = `/food/${aiCatKey}o.png`;
    const aiSpriteCatch = `/food/${aiCatKey}m.png`;

    useEffect(() => {
        addHappinessRef.current = addHappiness;
        addHungerRef.current = addHunger;
    }, [addHappiness, addHunger]);

    useEffect(() => {
        playerRef.current = player;
    }, [player]);

    useEffect(() => {
        aiPlayerRef.current = aiPlayer;
    }, [aiPlayer]);

    useEffect(() => {
        if (gameState !== 'playing') return;

        const handleKeyDown = (e: KeyboardEvent) => {
            const speed = 20;

            if (e.key === 'ArrowLeft' || e.key === 'a') {
                setPlayer(p => {
                    const nextPlayer = { ...p, x: Math.max(0, p.x - speed) };
                    playerRef.current = nextPlayer;
                    return nextPlayer;
                });
            } else if (e.key === 'ArrowRight' || e.key === 'd') {
                setPlayer(p => {
                    const nextPlayer = { ...p, x: Math.min(GAME_WIDTH - p.width, p.x + speed) };
                    playerRef.current = nextPlayer;
                    return nextPlayer;
                });
            }
        };

        window.addEventListener('keydown', handleKeyDown);
        return () => window.removeEventListener('keydown', handleKeyDown);
    }, [gameState]);

    const handlePointerMove = useCallback((e: PointerEvent<HTMLDivElement>) => {
        if (gameState !== 'playing' || !gameRef.current) return;

        const rect = gameRef.current.getBoundingClientRect();
        const pointerRatioX = (e.clientX - rect.left) / rect.width;
        const x = pointerRatioX * GAME_WIDTH - PLAYER_WIDTH / 2;
        const nextX = Math.max(0, Math.min(GAME_WIDTH - playerRef.current.width, x));

        playerRef.current = {
            ...playerRef.current,
            x: nextX,
        };

        if (pointerFrameRef.current !== null) return;

        pointerFrameRef.current = requestAnimationFrame(() => {
            setPlayer(playerRef.current);
            pointerFrameRef.current = null;
        });
    }, [gameState]);

    const spawnFood = useCallback(() => {
        let attempts = 0;
        let foodType = FOOD_EMOJIS[Math.floor(Math.random() * FOOD_EMOJIS.length)];

        while (attempts < 6 && foodType.pickup) {
            const p = foodType.pickup;
            if ((p === 'magnetic' && pickupCountsRef.current.magnetic >= 2)
                || (p === 'happiness' && pickupCountsRef.current.happiness >= 2)) {
                const nonPickups = FOOD_EMOJIS.filter(f => !f.pickup);
                foodType = nonPickups[Math.floor(Math.random() * nonPickups.length)];
                break;
            }
            attempts++;
            break;
        }

        const spawnPadding = 18;
        const newFood: FoodItem = {
            id: Date.now() + Math.random(),
            x: spawnPadding + Math.random() * (GAME_WIDTH - 40 - spawnPadding * 2),
            y: -40,
            emoji: foodType.emoji,
            points: foodType.points,
            speed: 2 + Math.random() * 3,
            pickup: (foodType as any).pickup,
        };

        setFoods(prev => [...prev, newFood]);

        if ((foodType as any).pickup === 'magnetic') pickupCountsRef.current.magnetic += 1;
        if ((foodType as any).pickup === 'happiness') pickupCountsRef.current.happiness += 1;
    }, []);

    const moveAi = useCallback((currentFoods: FoodItem[]) => {
        if (!aiEnabled) {
            return aiPlayerRef.current;
        }

        const currentAi = aiPlayerRef.current;
        const candidates = currentFoods.filter(food =>
            food.y > 10
            && food.y < GAME_HEIGHT - 80
            && (food.points > 0 || food.pickup)
        );

        let targetX = GAME_WIDTH / 2;

        if (candidates.length > 0) {
            const bestFood = candidates.sort((a, b) => {
                const scoreA = a.points * 100 + a.y;
                const scoreB = b.points * 100 + b.y;
                return scoreB - scoreA;
            })[0];

            targetX = bestFood.x;
        }

        const aiCenter = currentAi.x + currentAi.width / 2;
        const targetCenter = targetX + 18;
        const distance = targetCenter - aiCenter;
        const maxStep = 5.4;
        const step = Math.max(-maxStep, Math.min(maxStep, distance));
        const nextX = Math.max(0, Math.min(GAME_WIDTH - currentAi.width, currentAi.x + step));
        const nextAi = { ...currentAi, x: nextX };

        aiPlayerRef.current = nextAi;
        setAiPlayer(nextAi);

        return nextAi;
    }, [aiEnabled]);

    useEffect(() => {
        if (gameState !== 'playing') return;

        const gameLoop = (timestamp: number) => {
            if (timestamp - lastSpawnRef.current > 760) {
                spawnFood();
                lastSpawnRef.current = timestamp;
            }

            setFoods(prev => {
                const currentPlayer = playerRef.current;
                const nextAi = moveAi(prev);
                const newFoods: FoodItem[] = [];
                let aiDelta = 0;
                let aiCaughtSomething = false;

                prev.forEach(food => {
                    let newX = food.x;
                    const newY = food.y + food.speed;

                    if (magneticActive) {
                        const playerCenterX = currentPlayer.x + currentPlayer.width / 2;
                        const foodCenterX = food.x + 20;
                        const distance = playerCenterX - foodCenterX;
                        const magneticForce = 0.05;
                        newX += distance * magneticForce;
                    }

                    const foodCenter = newX + 20;
                    const playerLeft = currentPlayer.x;
                    const playerRight = currentPlayer.x + currentPlayer.width;
                    const aiLeft = nextAi.x;
                    const aiRight = nextAi.x + nextAi.width;

                    const caughtByPlayer =
                        newY > HUMAN_COLLISION_MIN_Y
                        && newY < HUMAN_COLLISION_MAX_Y
                        && foodCenter > playerLeft
                        && foodCenter < playerRight;

                    const caughtByAI =
                        aiEnabled
                        && newY > AI_COLLISION_MIN_Y
                        && newY < AI_COLLISION_MAX_Y
                        && foodCenter > aiLeft
                        && foodCenter < aiRight;

                    if (caughtByPlayer) {
                        if (food.pickup === 'magnetic') {
                            setMagneticActive(true);
                        } else if (food.pickup === 'happiness') {
                            setHappinessMultiplier(prevMultiplier => prevMultiplier + 1);
                        } else {
                            setHungerPoints(prevPoints => prevPoints + food.points);
                            setHappinessPoints(prevPoints => prevPoints + food.points * happinessMultiplier);
                        }

                        setIsCatching(true);
                        if (catchTimeoutRef.current) clearTimeout(catchTimeoutRef.current);
                        catchTimeoutRef.current = setTimeout(() => setIsCatching(false), 200);
                    } else if (caughtByAI) {
                        if (!food.pickup) {
                            aiDelta += food.points;
                        } else {
                            aiDelta += 1;
                        }

                        aiCaughtSomething = true;
                    } else if (newY < GAME_HEIGHT) {
                        newFoods.push({ ...food, x: newX, y: newY });
                    }
                });

                if (aiDelta !== 0) {
                    setAiScore(prevScore => prevScore + aiDelta);
                }

                if (aiCaughtSomething) {
                    setIsAiCatching(true);
                    if (aiCatchTimeoutRef.current) clearTimeout(aiCatchTimeoutRef.current);
                    aiCatchTimeoutRef.current = setTimeout(() => setIsAiCatching(false), 200);
                }

                return newFoods;
            });

            animationRef.current = requestAnimationFrame(gameLoop);
        };

        animationRef.current = requestAnimationFrame(gameLoop);

        return () => {
            if (animationRef.current !== null) {
                cancelAnimationFrame(animationRef.current);
                animationRef.current = null;
            }
        };
    }, [gameState, spawnFood, moveAi, magneticActive, happinessMultiplier, aiEnabled]);

    useEffect(() => {
        if (!magneticActive) return;

        const timeout = setTimeout(() => setMagneticActive(false), 15000);
        return () => clearTimeout(timeout);
    }, [magneticActive]);

    useEffect(() => {
        if (gameState !== 'playing') return;

        const timer = setInterval(() => {
            setTimeLeft(t => {
                if (t <= 1) {
                    setGameState('finished');
                    return 0;
                }
                return t - 1;
            });
        }, 1000);

        return () => clearInterval(timer);
    }, [gameState]);

    const updateGameScale = useCallback(() => {
        const availableWidth = Math.max(260, window.innerWidth - 40);
        const availableHeight = Math.max(220, window.innerHeight - 320);
        const widthScale = Math.min(1, availableWidth / GAME_WIDTH);
        const heightScale = Math.min(1, availableHeight / GAME_HEIGHT);
        const newScale = Math.max(0.38, Math.min(widthScale, heightScale));
        setGameScale(newScale);
    }, []);

    useEffect(() => {
        updateGameScale();
        window.addEventListener('resize', updateGameScale);
        return () => window.removeEventListener('resize', updateGameScale);
    }, [updateGameScale]);

    useEffect(() => {
        return () => {
            if (catchTimeoutRef.current) clearTimeout(catchTimeoutRef.current);
            if (aiCatchTimeoutRef.current) clearTimeout(aiCatchTimeoutRef.current);
            if (pointerFrameRef.current !== null) cancelAnimationFrame(pointerFrameRef.current);
        };
    }, []);

    useEffect(() => {
        if (gameState === 'finished' && !happinessAddedRef.current) {
            happinessAddedRef.current = true;
            const happiness = Math.max(0, Math.floor(happinessPoints / 10));
            const appliedHappiness = Math.min(happiness, Math.max(0, 100 - pet.happiness));
            setHappinessGained(appliedHappiness);
            addHappinessRef.current(happiness);
        }
    }, [gameState, happinessPoints, pet.happiness]);

    useEffect(() => {
        if (gameState === 'finished' && !hungerAddedRef.current) {
            hungerAddedRef.current = true;
            const hunger = Math.max(0, hungerPoints);
            const appliedHunger = Math.min(hunger, Math.max(0, 100 - pet.hunger));
            setHungerLost(appliedHunger);
            addHungerRef.current(hunger);
        }
    }, [gameState, hungerPoints, pet.hunger]);

    const startGame = (withAI: boolean) => {
        const initialPlayer = { x: GAME_WIDTH / 2 - PLAYER_WIDTH / 2, width: PLAYER_WIDTH };
        const initialAI = { x: GAME_WIDTH / 2 + 120, width: PLAYER_WIDTH };

        setGameState('playing');
        setTimeLeft(GAME_DURATION);
        setFoods([]);
        setPlayer(initialPlayer);
        playerRef.current = initialPlayer;
        setAiPlayer(initialAI);
        aiPlayerRef.current = initialAI;
        setAiEnabled(withAI);
        setHappinessGained(0);
        setHungerLost(0);
        setHungerPoints(0);
        setHappinessPoints(0);
        setAiScore(0);
        setIsCatching(false);
        setIsAiCatching(false);
        lastSpawnRef.current = 0;
        happinessAddedRef.current = false;
        hungerAddedRef.current = false;
        pickupCountsRef.current = { magnetic: 0, happiness: 0 };
        setHappinessMultiplier(1);
        setMagneticActive(false);
    };

    const score = hungerPoints + happinessPoints;
    const playerScale = isCatching ? 1.2 : 1;
    const aiScale = isAiCatching ? 1.15 : 1;
    const scaledPlayerWidth = player.width * playerScale;
    const scaledAiWidth = aiPlayer.width * aiScale;
    const playerLeft = Math.max(0, Math.min(player.x, GAME_WIDTH - scaledPlayerWidth));
    const aiLeft = Math.max(0, Math.min(aiPlayer.x, GAME_WIDTH - scaledAiWidth));
    const playerWon = score >= aiScore;

    return (
        <GameContainer>
            <CanvasBackground>
                <StyledCanvasWrapper />
            </CanvasBackground>

            <GameContent>
                <Header>
                    <HeaderRow>
                        <HeaderBox>
                            <HeaderLabel color="#fbbf24">hunger</HeaderLabel>
                            <HeaderValue>{hungerPoints}</HeaderValue>
                        </HeaderBox>

                        <HeaderBoxCenter>
                            <HeaderLabel color="#fbbf24">
                                🍱 +2 🍖 +2 🌮 +2 🍔 +1 🧋 +1 🍛 +1 🍧 0 🥦 -1 🥗 -2 🧲 attract food 💛 bonus x2
                            </HeaderLabel>
                        </HeaderBoxCenter>

                        <HeaderBox>
                            <HeaderLabel color="#f472b6">happiness</HeaderLabel>
                            <HeaderValue>{happinessPoints}</HeaderValue>
                        </HeaderBox>

                        {aiEnabled && (
                            <HeaderBox>
                                <HeaderLabel color="#60a5fa">AI</HeaderLabel>
                                <HeaderValue>{aiScore}</HeaderValue>
                            </HeaderBox>
                        )}
                    </HeaderRow>

                    <HeaderTimerRow>
                        <HeaderBox isTimer danger={timeLeft <= 10}>
                            ⏱ {timeLeft}s
                        </HeaderBox>
                    </HeaderTimerRow>
                </Header>

                <GameAreaWrapper
                    ref={gameRef}
                    onPointerMove={handlePointerMove}
                    onPointerDown={handlePointerMove}
                    gameScale={gameScale}
                    data-playing={gameState === 'playing'}
                >
                    <GameBackground gameScale={gameScale}>
                        {foods.map(food => (
                            <FoodEmoji
                                key={food.id}
                                style={{
                                    transform: `translate3d(${Math.max(0, Math.min(GAME_WIDTH - 36, food.x))}px, ${food.y}px, 0)`,
                                }}
                            >
                                {food.emoji}
                            </FoodEmoji>
                        ))}

                        {gameState === 'playing' && (
                            <>
                                {aiEnabled && (
                                    <PlayerContainer
                                        style={{
                                            left: aiLeft,
                                            bottom: AI_BOTTOM,
                                        }}
                                        playerScale={aiScale}
                                        isAI
                                    >
                                        <PlayerImage
                                            src={isAiCatching ? aiSpriteCatch : aiSpriteIdle}
                                            alt="AI cat"
                                            draggable={false}
                                        />
                                        <AiNameTag>AI</AiNameTag>
                                    </PlayerContainer>
                                )}

                                <PlayerContainer
                                    style={{
                                        left: playerLeft,
                                        bottom: HUMAN_BOTTOM,
                                    }}
                                    playerScale={playerScale}
                                >
                                    <PlayerImage
                                        src={isCatching ? playerSpriteCatch : playerSpriteIdle}
                                        alt="Player cat"
                                        draggable={false}
                                    />
                                </PlayerContainer>
                            </>
                        )}
                    </GameBackground>

                    {gameState === 'waiting' && (
                        <WaitingScreenContent>
                            <ScreenTitle>Food Catch</ScreenTitle>
                            <ScreenSubtitle>
                                Catch the food to score points!
                            </ScreenSubtitle>
                            <ScreenInstruction>
                                Use the mouse or arrow keys ← →
                            </ScreenInstruction>
                            <ButtonGroup>
                                <PrimaryButton onClick={() => startGame(false)}>
                                    🎮 Play
                                </PrimaryButton>
                                <SecondaryButton onClick={() => startGame(true)}>
                                    🤖 Play vs AI
                                </SecondaryButton>
                            </ButtonGroup>
                        </WaitingScreenContent>
                    )}

                    {gameState === 'finished' && (
                        <FinishedScreenContent>
                            <FinishedContainer>
                                <ScreenTitle>
                                    Time's up!
                                </ScreenTitle>

                                {aiEnabled ? (
                                    <>
                                        <ScoreDisplay>
                                            You: {score} points | AI: {aiScore} points
                                        </ScoreDisplay>
                                        <ResultMessage won={playerWon}>
                                            {playerWon ? '🏆 You beat the AI!' : '🤖 The AI wins this round!'}
                                        </ResultMessage>
                                    </>
                                ) : (
                                    <ScoreDisplay>
                                        {score} points
                                    </ScoreDisplay>
                                )}

                                <RewardMessage>
                                    Your Nekotchi is {happinessGained} more happier and {hungerLost} less hungry!
                                </RewardMessage>
                            </FinishedContainer>
                            <ButtonGroup>
                                <SecondaryButton onClick={() => startGame(aiEnabled)}>
                                    🔄 Play again!
                                </SecondaryButton>
                            </ButtonGroup>
                        </FinishedScreenContent>
                    )}
                </GameAreaWrapper>

                <BackButton onClick={() => navigate('/games')}>
                    ← Back
                </BackButton>
                <ReturnButton onClick={() => navigate('/nekotchi/me')}>
                    ← Let's return to your Nekotchi!
                </ReturnButton>
            </GameContent>
        </GameContainer>
    );
}