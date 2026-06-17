import styled from 'styled-components';
import { useState, useEffect, useCallback, useRef } from 'react';
import { useNavigate } from 'react-router-dom';
import { usePet } from '../../context/PetContext';
import { useSocket } from '../../hooks/useSocket';

const GAME_WIDTH = 900;
const GAME_HEIGHT = 500;
const RACE_DISTANCE = 500;
const SCROLL_SPEED = 8;
const FRAME_WIDTH = 50;
const SPRITE_HEIGHT = 70;
const TOTAL_FRAMES = 6;

const GameContainer = styled.div`
  width: 100%;
  min-height: 100vh;
  position: relative;
  overflow: hidden;
`;

const Background = styled.div`
  position: absolute;
  inset: 0;
  z-index: 0;
  background: linear-gradient(180deg, #1a1a3a 0%, #2a1a4e 50%, #4a2a6e 100%);
`;

const ContentWrapper = styled.div`
  position: relative;
  z-index: 1;
  height: 100%;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 20px;
`;

const MenuCard = styled.div`
  width: 100%;
  max-width: 620px;
  background: rgba(30, 20, 50, 0.95);
  border-radius: 20px;
  padding: 40px;
  text-align: center;
  border: 3px solid #8b5cf6;
  box-shadow: 0 0 40px rgba(139, 92, 246, 0.5);
`;

const MenuTitle = styled.h1`
  color: #fff;
  font-size: 36px;
  margin-bottom: 10px;
`;

const ButtonGroup = styled.div`
  display: flex;
  flex-direction: column;
  gap: 15px;
`;

const AiButtonRow = styled.div`
  display: flex;
  gap: 10px;
  justify-content: center;
  flex-wrap: wrap;
`;

const SectionLabel = styled.p`
  color: #a78bfa;
  margin-bottom: 5px;
`;

const PrimaryButton = styled.button`
  padding: 12px 30px;
  font-size: 16px;
  background: linear-gradient(135deg, #10b981, #059669);
  color: white;
  border: none;
  border-radius: 10px;
  cursor: pointer;
  font-weight: bold;
  margin-bottom: 10px;
  width: 100%;
  transition: opacity 0.2s;

  &:hover {
    opacity: 0.9;
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const SecondaryButton = styled.button`
  width: 100%;
  padding: 12px 20px;
  font-size: 16px;
  background: linear-gradient(135deg, #3b82f6, #2563eb);
  color: white;
  border: none;
  border-radius: 10px;
  cursor: pointer;
  font-weight: bold;
`;

const AiButton = styled.button`
  flex: 1 1 120px;
  padding: 12px 20px;
  font-size: 14px;
  background: linear-gradient(135deg, #7c3aed, #2563eb);
  color: white;
  border: none;
  border-radius: 10px;
  cursor: pointer;
  font-weight: bold;

  &:hover {
    opacity: 0.9;
  }
`;

const SpectatorButton = styled.button`
  padding: 12px 30px;
  font-size: 16px;
  background: linear-gradient(135deg, #6d28d9, #8b5cf6);
  color: white;
  border: none;
  border-radius: 10px;
  cursor: pointer;
  font-weight: bold;
  margin-bottom: 10px;
  width: 100%;
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

const CancelButton = styled.button`
  margin-top: 15px;
  width: 100%;
  display: block;
  padding: 10px 20px;
  background: transparent;
  border: 2px solid #6b7280;
  border-radius: 10px;
  color: #9ca3af;
  cursor: pointer;
`;

const Divider = styled.div`
  border-top: 1px solid #4a3a6a;
  margin: 10px 0;
  padding-top: 20px;
`;

const InputContainer = styled.div`
  display: flex;
  gap: 10px;
  flex-direction: column;
`;

const RoomInput = styled.input`
  width: 100%;
  padding: 12px;
  border-radius: 10px;
  border: 2px solid #4a3a6a;
  background: rgba(30, 20, 50, 0.8);
  color: white;
  font-size: 16px;
  text-align: center;
  text-transform: uppercase;

  &::placeholder {
    color: #6b7280;
  }
`;

const WaitingRoomCard = styled.div`
  width: 100%;
  max-width: 520px;
  background: rgba(30, 20, 50, 0.95);
  border-radius: 20px;
  padding: 40px;
  text-align: center;
  border: 3px solid #10b981;
  box-shadow: 0 0 40px rgba(16, 185, 129, 0.5);
`;

const WaitingRoomTitle = styled.h2`
  color: #fff;
  margin-bottom: 10px;
`;

const CodeBox = styled.div`
  background: rgba(16, 185, 129, 0.2);
  padding: 15px 30px;
  border-radius: 10px;
  margin-bottom: 20px;
`;

const CodeLabel = styled.p`
  color: #a78bfa;
  font-size: 14px;
`;

const CodeText = styled.p`
  color: #10b981;
  font-size: 32px;
  font-weight: bold;
  letter-spacing: 5px;
`;

const PlayersSection = styled.div`
  margin-bottom: 20px;
`;

const PlayersLabel = styled.p`
  color: #a78bfa;
  margin-bottom: 10px;
`;

const PlayerItem = styled.div<{ isLocal?: boolean }>`
  background: ${props => props.isLocal ? 'rgba(74, 222, 128, 0.2)' : 'rgba(96, 165, 250, 0.2)'};
  padding: 10px;
  border-radius: 8px;
  margin-bottom: 5px;
  color: ${props => props.isLocal ? '#4ade80' : '#60a5fa'};
`;

const EmptySlot = styled.div`
  border: 2px dashed #4a3a6a;
  padding: 10px;
  border-radius: 8px;
  color: #6b7280;
`;

const StartRaceButton = styled.button`
  padding: 15px 40px;
  font-size: 18px;
  background: ${props => props.disabled ? '#4a3a6a' : 'linear-gradient(135deg, #10b981, #059669)'};
  color: white;
  border: none;
  border-radius: 12px;
  cursor: ${props => props.disabled ? 'not-allowed' : 'pointer'};
  font-weight: bold;
`;

const CountdownOverlay = styled.div`
  position: absolute;
  inset: 0;
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 100;

  @keyframes pulse {
    0% {
      transform: scale(0.5);
      opacity: 0;
    }
    50% {
      transform: scale(1.2);
      opacity: 1;
    }
    100% {
      transform: scale(1);
      opacity: 1;
    }
  }
`;

const CountdownText = styled.div`
  font-size: 150px;
  font-weight: bold;
  color: #fff;
  text-shadow: 0 0 50px rgba(139, 92, 246, 0.8);
  animation: pulse 1s ease-in-out;
`;

const RaceTrack = styled.div<{ gameScale?: number }>`
  width: 100%;
  max-width: ${GAME_WIDTH}px;
  height: ${props => GAME_HEIGHT * (props.gameScale || 1)}px;
  border-radius: 20px;
  position: relative;
  overflow: hidden;
  border: 3px solid #4a3a6a;
`;

const RaceTrackBackground = styled.div<{ scrollOffset?: number; gameScale?: number }>`
  width: ${GAME_WIDTH}px;
  height: ${GAME_HEIGHT}px;
  background-image: url(/game/course-bg.jpg);
  background-size: cover;
  background-position: ${props => `${-(props.scrollOffset || 0) * 0.3}px center`};
  image-rendering: pixelated;
  position: relative;
  transform: ${props => `scale(${props.gameScale || 1})`};
  transform-origin: top left;
`;

const StartLine = styled.div<{ scrollOffset?: number }>`
  position: absolute;
  left: ${props => 150 - (props.scrollOffset || 0)}px;
  top: 100px;
  bottom: 0;
  width: 4px;
  background: repeating-linear-gradient(
    180deg,
    #fff 0px,
    #fff 10px,
    #333 10px,
    #333 20px
  );
`;

const FinishLine = styled.div<{ scrollOffset?: number }>`
  position: absolute;
  left: ${props => 150 + (RACE_DISTANCE * SCROLL_SPEED) - (props.scrollOffset || 0)}px;
  top: 100px;
  bottom: 0;
  width: 20px;
  background: repeating-linear-gradient(180deg, #fff 0px, #fff 10px, #333 10px, #333 20px),
              repeating-linear-gradient(90deg, #fff 0px, #fff 10px, #333 10px, #333 20px);
  background-size: 10px 10px;
`;

const FinishFlag = styled.div<{ scrollOffset?: number }>`
  position: absolute;
  left: ${props => 170 + (RACE_DISTANCE * SCROLL_SPEED) - (props.scrollOffset || 0)}px;
  top: 70px;
  font-size: 30px;
`;

const ProgressBarsContainer = styled.div`
  position: absolute;
  top: 10px;
  left: 10px;
  right: 10px;
`;

const ProgressBarItem = styled.div`
  margin-bottom: 8px;
`;

const ProgressBarLabel = styled.div<{ isLocal?: boolean }>`
  display: flex;
  justify-content: space-between;
  color: ${props => props.isLocal ? '#4ade80' : '#60a5fa'};
  font-size: 12px;
  margin-bottom: 2px;
`;

const ProgressBarBackground = styled.div`
  height: 8px;
  background: rgba(0, 0, 0, 0.5);
  border-radius: 4px;
  overflow: hidden;
`;

const ProgressBarFill = styled.div<{ percentage?: number; isLocal?: boolean }>`
  height: 100%;
  width: ${props => `${props.percentage || 0}%`};
  background: ${props => props.isLocal
    ? 'linear-gradient(90deg, #4ade80, #22c55e)'
    : 'linear-gradient(90deg, #60a5fa, #3b82f6)'};
  border-radius: 4px;
  transition: width 0.1s;
`;

const ControlsHint = styled.div`
  position: absolute;
  bottom: 20px;
  left: 50%;
  transform: translateX(-50%);
  background: rgba(0, 0, 0, 0.7);
  padding: 8px 20px;
  border-radius: 20px;
  color: #a78bfa;
  font-size: 14px;
`;

const WinnerOverlay = styled.div`
  position: absolute;
  inset: 0;
  display: flex;
  align-items: center;
  justify-content: center;
  background: rgba(0, 0, 0, 0.8);
  z-index: 100;
`;

const WinnerCard = styled.div<{ isWinner?: boolean }>`
  width: 100%;
  max-width: 520px;
  background: rgba(30, 20, 50, 0.95);
  border-radius: 20px;
  padding: 40px;
  text-align: center;
  border: 3px solid ${props => props.isWinner ? '#4ade80' : '#f87171'};
  box-shadow: 0 0 40px ${props => props.isWinner ? 'rgba(74, 222, 128, 0.5)' : 'rgba(248, 113, 113, 0.3)'};
`;

const WinnerEmoji = styled.div`
  font-size: 60px;
  margin-bottom: 10px;
`;

const WinnerTitle = styled.h2<{ isWinner?: boolean }>`
  color: ${props => props.isWinner ? '#4ade80' : '#f87171'};
  font-size: 28px;
  margin-bottom: 10px;
`;

const WinnerMessage = styled.p`
  color: #a78bfa;
  margin-bottom: 20px;
`;

const HappinessBox = styled.div`
  background: rgba(74, 222, 128, 0.2);
  padding: 10px 20px;
  border-radius: 10px;
  margin-bottom: 20px;
  color: #4ade80;
`;

const WinnerButtonGroup = styled.div`
  display: flex;
  gap: 10px;
  justify-content: center;
`;

const WinnerButton = styled.button<{ secondary?: boolean }>`
  padding: 12px 30px;
  font-size: 16px;
  background: ${props => props.secondary ? 'transparent' : 'linear-gradient(135deg, #8b5cf6, #6d28d9)'};
  color: ${props => props.secondary ? '#9ca3af' : 'white'};
  border: ${props => props.secondary ? '2px solid #6b7280' : 'none'};
  border-radius: 10px;
  cursor: pointer;
  font-weight: bold;
`;

const QuitButton = styled.button`
  position: absolute;
  top: 20px;
  left: 20px;
  padding: 10px 20px;
  background: rgba(30, 20, 50, 0.8);
  border: 2px solid #6b7280;
  border-radius: 10px;
  color: #9ca3af;
  cursor: pointer;
  z-index: 50;
`;

const NekotchiRacerContainer = styled.div<{ progressX?: number; offsetY?: number }>`
  position: absolute;
  left: ${props => `${props.progressX || 0}px`};
  top: ${props => `${props.offsetY || 0}px`};
  transition: left 0.1s ease-out;
  z-index: 10;
`;

const NekotchiSprite = styled.div<{ frame?: number; isMoving?: boolean; isLocal?: boolean }>`
  width: ${FRAME_WIDTH * 2}px;
  height: ${SPRITE_HEIGHT * 2}px;
  position: relative;
  transform: ${props => `scaleX(-1) ${props.isMoving ? 'translateY(-3px)' : ''}`};
  transition: transform 0.1s;
  background-image: url(/witchcat/fly.png);
  background-position: ${props => `-${(props.frame || 0) * FRAME_WIDTH * 2}px 0`};
  background-size: ${TOTAL_FRAMES * FRAME_WIDTH * 2}px ${SPRITE_HEIGHT * 2}px;
  background-repeat: no-repeat;
  image-rendering: pixelated;
  filter: ${props => props.isLocal ? 'none' : 'hue-rotate(180deg)'};
`;

const NekotchiName = styled.div<{ isLocal?: boolean }>`
  text-align: center;
  color: ${props => props.isLocal ? '#4ade80' : '#60a5fa'};
  font-size: 12px;
  font-weight: bold;
  text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.8);
  margin-top: 2px;
`;

interface RacePlayer {
    id: string;
    name: string;
    progress: number;
    y: number;
    color: string;
    isLocal: boolean;
}

interface RoomInfo {
    roomId: string;
    players: RacePlayer[];
    status: 'waiting' | 'countdown' | 'racing' | 'finished';
    countdown?: number;
    winner?: string;
    winnerId?: string;
}

type GameState = 'menu' | 'waiting' | 'spectating' | 'countdown' | 'racing' | 'finished';
type AiDifficulty = 'easy' | 'normal' | 'hard';

interface AiSettings {
    baseSpeed: number;
    variation: number;
    mistakeChance: number;
    pauseChance: number;
    burstChance: number;
    burstBonus: number;
    name: string;
    color: string;
}

const AI_PRESETS: Record<AiDifficulty, AiSettings> = {
    easy: {
        baseSpeed: 0.32,
        variation: 0.02,
        mistakeChance: 0.08,
        pauseChance: 0.03,
        burstChance: 0.00,
        burstBonus: 0.00,
        name: 'Easy',
        color: '#22c55e',
    },
    normal: {
        baseSpeed: 0.78,
        variation: 0.03,
        mistakeChance: 0.02,
        pauseChance: 0.005,
        burstChance: 0.01,
        burstBonus: 0.08,
        name: 'Normal',
        color: '#f59e0b',
    },
    hard: {
        baseSpeed: 1.05,
        variation: 0.04,
        mistakeChance: 0.01,
        pauseChance: 0.002,
        burstChance: 0.035,
        burstBonus: 0.22,
        name: 'Hard',
        color: '#ef4444',
    },
};

const NekotchiRacer = ({
    player,
    offsetY,
    isMoving,
    localProgress
}: {
    player: RacePlayer;
    offsetY: number;
    isMoving: boolean;
    localProgress: number;
}) => {
    const relativeProgress = player.progress - localProgress;
    const progressX = 150 + relativeProgress * SCROLL_SPEED;
    const [frame, setFrame] = useState(0);

    useEffect(() => {
        const interval = setInterval(() => {
            setFrame(prev => (prev + 1) % TOTAL_FRAMES);
        }, 120);

        return () => clearInterval(interval);
    }, []);

    return (
        <NekotchiRacerContainer progressX={progressX} offsetY={offsetY}>
            <NekotchiSprite
                frame={frame}
                isMoving={isMoving}
                isLocal={player.isLocal}
            />
            <NekotchiName isLocal={player.isLocal}>
                {player.name}
            </NekotchiName>
        </NekotchiRacerContainer>
    );
};

export default function CourseGame() {
    const navigate = useNavigate();
    const { pet, addHappiness, color: petColor } = usePet();
    const token = localStorage.getItem('auth_token') ?? localStorage.getItem('token') ?? undefined;
    const { isConnected, emit, on, off } = useSocket({ autoConnect: true, token });

    const [gameState, setGameState] = useState<GameState>('menu');
    const [roomCode, setRoomCode] = useState('');
    const [inputRoomCode, setInputRoomCode] = useState('');
    const [players, setPlayers] = useState<RacePlayer[]>([]);
    const [countdown, setCountdown] = useState(3);
    const [winner, setWinner] = useState<string | null>(null);
    const [winnerId, setWinnerId] = useState<string | null>(null);
    const [happinessGained, setHappinessGained] = useState(0);
    const [gameScale, setGameScale] = useState(1);
    const [spectatorMode, setSpectatorMode] = useState(false);
    const [notification, setNotification] = useState<string | null>(null);

    const localPlayerRef = useRef<RacePlayer | null>(null);
    const lastKeyPressRef = useRef<number>(0);
    const speedBoostRef = useRef<number>(0);
    const aiAnimationRef = useRef<number>();
    const spectatorModeRef = useRef(false);
    const addHappinessRef = useRef(addHappiness);
    const happinessAddedRef = useRef(false);
    const aiSettingsRef = useRef<AiSettings>(AI_PRESETS.normal);

    const updateGameScale = useCallback(() => {
        const availableWidth = Math.min(window.innerWidth - 40, GAME_WIDTH);
        const newScale = Math.max(0.6, Math.min(1, availableWidth / GAME_WIDTH));
        setGameScale(newScale);
    }, []);

    useEffect(() => {
        updateGameScale();
        window.addEventListener('resize', updateGameScale);
        return () => window.removeEventListener('resize', updateGameScale);
    }, [updateGameScale]);

    useEffect(() => {
        addHappinessRef.current = addHappiness;
    }, [addHappiness]);

    useEffect(() => {
        spectatorModeRef.current = spectatorMode;
    }, [spectatorMode]);

    const localPlayer = players.find(p => p.isLocal);
    const leadingPlayer = [...players].sort((a, b) => b.progress - a.progress)[0];
    const scrollOffset = spectatorMode
        ? (leadingPlayer ? leadingPlayer.progress * SCROLL_SPEED : 0)
        : (localPlayer ? localPlayer.progress * SCROLL_SPEED : 0);

    const initLocalPlayer = useCallback(() => {
        const player: RacePlayer = {
            id: 'local-' + Date.now(),
            name: pet.name,
            progress: 0,
            y: 150,
            color: petColor,
            isLocal: true,
        };

        localPlayerRef.current = player;
        return player;
    }, [petColor, pet.name]);

    useEffect(() => {
        if (!isConnected) return;

        on<RoomInfo>('room:joined', (data) => {
            setRoomCode(data.roomId);
            setPlayers(data.players.map(p => ({
                ...p,
                isLocal: p.id === localPlayerRef.current?.id,
            })));
            setGameState(spectatorModeRef.current ? 'spectating' : 'waiting');
        });

        on<RoomInfo>('room:updated', (data) => {
            setPlayers(prev =>
                data.status === 'waiting' || data.status === 'countdown'
                    ? data.players.map(p => ({ ...p, isLocal: p.id === localPlayerRef.current?.id }))
                    : prev
            );

            if (data.status === 'countdown') {
                setGameState(spectatorModeRef.current ? 'spectating' : 'countdown');
                setCountdown(data.countdown || 3);
            } else if (data.status === 'racing') {
                setGameState(spectatorModeRef.current ? 'spectating' : 'racing');
            } else if (data.status === 'finished' && data.winner) {
                setWinner(data.winner);
                setWinnerId(data.winnerId ?? null);
                setGameState('finished');
            }
        });

        on<{ playerId: string; progress: number }>('player:moved', (data) => {
            setPlayers(prev => prev.map(p =>
                p.id === data.playerId ? { ...p, progress: data.progress } : p
            ));
        });

        on<{ countdown: number }>('race:countdown', (data) => {
            setCountdown(data.countdown);
        });

        on<{ winner: string; winnerId: string }>('race:finished', (data) => {
            setWinner(data.winner);
            setWinnerId(data.winnerId);
            setGameState('finished');

            if (data.winnerId === localPlayerRef.current?.id && !happinessAddedRef.current) {
                happinessAddedRef.current = true;
                setHappinessGained(20);
                addHappinessRef.current(20);
            }
        });

        on<string>('room:error', (error) => {
            alert(error);
            setGameState('menu');
        });

        on<string>('room:start:error', (error) => {
            setNotification(error);
            setTimeout(() => setNotification(null), 3000);
        });

        on<RoomInfo>('spectate:joined', (data) => {
            setRoomCode(data.roomId);
            setPlayers(data.players);
            setGameState('spectating');
        });

        return () => {
            off('room:joined');
            off('room:updated');
            off('player:moved');
            off('race:countdown');
            off('race:finished');
            off('room:error');
            off('room:start:error');
            off('spectate:joined');
        };
    }, [isConnected, on, off]);

    useEffect(() => {
        if (gameState !== 'racing') return;

        const handleKeyDown = (e: KeyboardEvent) => {
            if (e.key !== 'ArrowRight' && e.key !== 'ArrowUp' && e.key !== ' ') {
                return;
            }

            e.preventDefault();

            const now = Date.now();
            const timeSinceLastPress = now - lastKeyPressRef.current;

            if (timeSinceLastPress < 200) {
                speedBoostRef.current = Math.min(speedBoostRef.current + 0.5, 3);
            } else {
                speedBoostRef.current = Math.max(speedBoostRef.current - 0.5, 0);
            }

            lastKeyPressRef.current = now;

            const moveAmount = 1 + speedBoostRef.current * 0.5;

            if (!localPlayerRef.current) {
                return;
            }

            localPlayerRef.current.progress = Math.min(
                RACE_DISTANCE,
                localPlayerRef.current.progress + moveAmount
            );

            setPlayers(prev => prev.map(p =>
                p.isLocal ? { ...p, progress: localPlayerRef.current!.progress } : p
            ));

            const hasSoloAI = players.some(p => !p.isLocal && p.id.startsWith('ai-'));

            if (isConnected && !hasSoloAI) {
                emit('player:move', { progress: localPlayerRef.current.progress });
            }

            if (hasSoloAI && localPlayerRef.current.progress >= RACE_DISTANCE && !winner) {
                setWinner(localPlayerRef.current.name);
                setWinnerId(localPlayerRef.current.id);
                setGameState('finished');

                if (!happinessAddedRef.current) {
                    happinessAddedRef.current = true;
                    setHappinessGained(20);
                    addHappinessRef.current(20);
                }
            }
        };

        window.addEventListener('keydown', handleKeyDown);
        return () => window.removeEventListener('keydown', handleKeyDown);
    }, [gameState, isConnected, emit, players, winner]);

    useEffect(() => {
    if (gameState !== 'racing') {
        return;
    }

    const moveAI = () => {
        setPlayers(prev => {
            const hasSoloAI = prev.some(p => !p.isLocal && p.id.startsWith('ai-'));

            if (!hasSoloAI) {
                return prev;
            }

            return prev.map(player => {
                if (player.isLocal || !player.id.startsWith('ai-')) {
                    return player;
                }

                const settings = aiSettingsRef.current;
                let aiSpeed = settings.baseSpeed + (Math.random() - 0.5) * settings.variation;

                if (Math.random() < settings.pauseChance) {
                    aiSpeed = 0;
                }

                if (Math.random() < settings.mistakeChance) {
                    aiSpeed *= 0.25;
                }

                if (Math.random() < settings.burstChance) {
                    aiSpeed += settings.burstBonus;
                }

                const newProgress = Math.min(RACE_DISTANCE, player.progress + aiSpeed);

                if (newProgress >= RACE_DISTANCE && !winner) {
                    setWinner(player.name);
                    setWinnerId(player.id);
                    setGameState('finished');
                }

                return {
                    ...player,
                    progress: newProgress,
                };
            });
        });

        aiAnimationRef.current = requestAnimationFrame(moveAI);
    };

    aiAnimationRef.current = requestAnimationFrame(moveAI);

    return () => {
        if (aiAnimationRef.current) {
            cancelAnimationFrame(aiAnimationRef.current);
        }
    };
}, [gameState, winner]);

    useEffect(() => {
        if (gameState !== 'countdown') return;

        const timer = setInterval(() => {
            setCountdown(prev => {
                if (prev <= 1) {
                    setGameState('racing');
                    return 0;
                }

                return prev - 1;
            });
        }, 1000);

        return () => clearInterval(timer);
    }, [gameState]);

    const createRoom = () => {
        const localPlayer = initLocalPlayer();

        if (isConnected) {
            emit('room:create', { player: localPlayer });
        } else {
            const code = Math.random().toString(36).substring(2, 8).toUpperCase();
            setRoomCode(code);
            setPlayers([localPlayer]);
            setGameState('waiting');
        }
    };

    const joinRoom = () => {
        if (!inputRoomCode.trim()) {
            alert('Entre un code de salle');
            return;
        }

        setSpectatorMode(false);

        const localPlayer = initLocalPlayer();

        if (isConnected) {
            emit('room:join', { roomId: inputRoomCode.toUpperCase(), player: localPlayer });
        } else {
            alert('Connexion au serveur requise pour rejoindre une salle');
        }
    };

    const watchRoom = () => {
        if (!inputRoomCode.trim()) {
            alert('Entre un code de salle');
            return;
        }

        setSpectatorMode(true);
        setRoomCode(inputRoomCode.toUpperCase());
        setPlayers([]);
        setWinner(null);
        setWinnerId(null);
        setCountdown(3);
        setGameState('spectating');

        if (isConnected) {
            emit('spectate:join', { roomId: inputRoomCode.toUpperCase() });
        } else {
            alert('Connect to the server to watch a race');
        }
    };

    const startSoloOnly = () => {
    const localPlayer = initLocalPlayer();

    setSpectatorMode(false);
    setRoomCode('');
    setWinner(null);
    setWinnerId(null);
    setHappinessGained(0);
    happinessAddedRef.current = false;
    speedBoostRef.current = 0;
    lastKeyPressRef.current = 0;

    if (aiAnimationRef.current) {
        cancelAnimationFrame(aiAnimationRef.current);
    }

    setPlayers([localPlayer]);
    setGameState('countdown');
    setCountdown(3);
};

    const startSoloRace = (difficulty: AiDifficulty) => {
        const localPlayer = initLocalPlayer();
        const settings = AI_PRESETS[difficulty];

        aiSettingsRef.current = settings;
        setSpectatorMode(false);
        setRoomCode('');
        setWinner(null);
        setWinnerId(null);
        setHappinessGained(0);
        happinessAddedRef.current = false;
        speedBoostRef.current = 0;
        lastKeyPressRef.current = 0;

        if (aiAnimationRef.current) {
            cancelAnimationFrame(aiAnimationRef.current);
        }

        const aiPlayer: RacePlayer = {
            id: 'ai-' + Date.now(),
            name: `AI Nekotchi ${settings.name}`,
            progress: 0,
            y: 250,
            color: settings.color,
            isLocal: false,
        };

        setPlayers([localPlayer, aiPlayer]);
        setGameState('countdown');
        setCountdown(3);
    };

    const startMultiplayerRace = () => {
        if (isConnected) {
            emit('room:start', { roomId: roomCode });
        } else {
            setGameState('countdown');
            setCountdown(3);
        }
    };

    const resetGame = () => {
        if (roomCode && (gameState === 'waiting' || gameState === 'finished' || gameState === 'racing')) {
            emit('room:leave', { roomId: roomCode });
        }

        setGameState('menu');
        setPlayers([]);
        setWinner(null);
        setWinnerId(null);
        setCountdown(3);
        setHappinessGained(0);
        happinessAddedRef.current = false;
        localPlayerRef.current = null;
        speedBoostRef.current = 0;
        lastKeyPressRef.current = 0;
        setSpectatorMode(false);

        if (aiAnimationRef.current) {
            cancelAnimationFrame(aiAnimationRef.current);
        }
    };

    const isMoving = Date.now() - lastKeyPressRef.current < 150;
    const isLocalWinner = winnerId !== null && winnerId === localPlayerRef.current?.id;

    return (
        <GameContainer>
            <Background />

            <ContentWrapper>
                {gameState === 'menu' && (
                    <MenuCard>
                        <MenuTitle>🏁 Nekotchi run</MenuTitle>

                        <ButtonGroup>
                            <SectionLabel>Solo</SectionLabel>

                        <SecondaryButton onClick={startSoloOnly}>
                            Solo
                        </SecondaryButton>

                        <Divider />

                        <SectionLabel>AI opponent</SectionLabel>

                        <AiButtonRow>
                            <AiButton onClick={() => startSoloRace('easy')}>
                                Easy
                            </AiButton>

                            <AiButton onClick={() => startSoloRace('normal')}>
                                Normal
                            </AiButton>

                            <AiButton onClick={() => startSoloRace('hard')}>
                                Hard
                            </AiButton>
                        </AiButtonRow>

                            <Divider />

                            <SectionLabel>Multiplayer</SectionLabel>

                            <PrimaryButton onClick={createRoom}>
                                ➕ Create a room
                            </PrimaryButton>

                            <InputContainer>
                                <RoomInput
                                    type="text"
                                    placeholder="Room Code"
                                    value={inputRoomCode}
                                    onChange={(e) => setInputRoomCode(e.target.value.toUpperCase())}
                                />
                                <SecondaryButton onClick={joinRoom}>
                                    Join
                                </SecondaryButton>
                            </InputContainer>

                            <Divider>
                                <SectionLabel style={{ marginBottom: '10px' }}>Spectator</SectionLabel>
                                <p style={{ color: '#c4b5fd', fontSize: '13px', marginBottom: '12px' }}>
                                    Look at a race in real-time with the room code.
                                </p>
                            </Divider>

                            <SpectatorButton onClick={watchRoom}>
                                👀 Watch a race
                            </SpectatorButton>
                        </ButtonGroup>

                        <BackButton onClick={() => navigate('/games')}>
                            ← Back
                        </BackButton>
                    </MenuCard>
                )}

                {gameState === 'waiting' && (
                    <WaitingRoomCard>
                        <WaitingRoomTitle>Waiting Room</WaitingRoomTitle>
                        <CodeBox>
                            <CodeLabel>Room Code</CodeLabel>
                            <CodeText>{roomCode}</CodeText>
                        </CodeBox>

                        <PlayersSection>
                            <PlayersLabel>Players ({players.length}/2)</PlayersLabel>
                            {players.map((p) => (
                                <PlayerItem key={p.id} isLocal={p.isLocal}>
                                    {p.name} {p.isLocal && '(You)'}
                                </PlayerItem>
                            ))}
                            {players.length < 2 && (
                                <EmptySlot>
                                    Waiting for a player...
                                </EmptySlot>
                            )}
                        </PlayersSection>

                        {notification && (
                            <div style={{
                                background: 'rgba(239, 68, 68, 0.2)',
                                border: '1px solid #ef4444',
                                borderRadius: '8px',
                                padding: '10px',
                                color: '#f87171',
                                marginBottom: '10px',
                                fontSize: '14px',
                            }}>
                                {notification}
                            </div>
                        )}

                        <StartRaceButton
                            onClick={startMultiplayerRace}
                            disabled={players.length < 1}
                        >
                            🚀 Start Race!
                        </StartRaceButton>

                        <CancelButton onClick={resetGame}>
                            Cancel
                        </CancelButton>
                    </WaitingRoomCard>
                )}

                {gameState === 'countdown' && (
                    <CountdownOverlay>
                        <CountdownText>
                            {countdown > 0 ? countdown : 'GO!'}
                        </CountdownText>
                    </CountdownOverlay>
                )}

                {(gameState === 'racing' || gameState === 'countdown' || gameState === 'finished' || gameState === 'spectating') && (
                    <RaceTrack gameScale={gameScale}>
                        <RaceTrackBackground scrollOffset={scrollOffset} gameScale={gameScale}>
                            <StartLine scrollOffset={scrollOffset} />
                            <FinishLine scrollOffset={scrollOffset} />
                            <FinishFlag scrollOffset={scrollOffset}>🏁</FinishFlag>

                            {players.map((player, index) => (
                                <NekotchiRacer
                                    key={player.id}
                                    player={player}
                                    offsetY={120 + index * 150}
                                    isMoving={player.isLocal && isMoving}
                                    localProgress={spectatorMode ? (leadingPlayer?.progress || 0) : (localPlayer?.progress || 0)}
                                />
                            ))}

                            <ProgressBarsContainer>
                                {players.map((player) => (
                                    <ProgressBarItem key={player.id}>
                                        <ProgressBarLabel isLocal={player.isLocal}>
                                            <span>{player.name}</span>
                                            <span>{Math.round((player.progress / RACE_DISTANCE) * 100)}%</span>
                                        </ProgressBarLabel>
                                        <ProgressBarBackground>
                                            <ProgressBarFill
                                                percentage={(player.progress / RACE_DISTANCE) * 100}
                                                isLocal={player.isLocal}
                                            />
                                        </ProgressBarBackground>
                                    </ProgressBarItem>
                                ))}
                            </ProgressBarsContainer>

                            {(gameState === 'racing' || gameState === 'spectating') && (
                                <ControlsHint>
                                    {gameState === 'spectating' ? 'Spectator Mode: No controls available' : 'Press ➡️ or ⬆️ or SPACE to move!'}
                                </ControlsHint>
                            )}
                        </RaceTrackBackground>
                    </RaceTrack>
                )}

                {gameState === 'finished' && winner && (
                    <WinnerOverlay>
                        <WinnerCard isWinner={isLocalWinner}>
                            <WinnerEmoji>
                                {spectatorMode ? '👀' : isLocalWinner ? '🏆' : '😿'}
                            </WinnerEmoji>
                            <WinnerTitle isWinner={!spectatorMode && isLocalWinner}>
                               {spectatorMode ? 'Race finished' : isLocalWinner ? 'Victory!' : 'Defeat...'}
                            </WinnerTitle>
                            <WinnerMessage>
                                {isLocalWinner ? 'You won the race!' : `${winner} won the race!`}
                            </WinnerMessage>

                            {happinessGained > 0 && (
                                <HappinessBox>
                                    +{happinessGained} 😊 Happiness
                                </HappinessBox>
                            )}

                            <WinnerButtonGroup>
                                <WinnerButton onClick={resetGame}>
                                    🔄 Play Again
                                </WinnerButton>
                                <WinnerButton secondary onClick={() => navigate('/games')}>
                                    Back
                                </WinnerButton>
                            </WinnerButtonGroup>
                        </WinnerCard>
                    </WinnerOverlay>
                )}

                {gameState === 'racing' && (
                    <QuitButton onClick={resetGame}>
                        ← Quit the race
                    </QuitButton>
                )}

                {gameState === 'spectating' && (
                    <QuitButton onClick={resetGame}>
                        ← Stop watching
                    </QuitButton>
                )}
            </ContentWrapper>
        </GameContainer>
    );
}