import { useRef, useState, useEffect } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import { Canvas, useFrame } from '@react-three/fiber';
import { Billboard, OrbitControls, Stars, Text } from '@react-three/drei';
import { Group } from 'three';
import * as THREE from 'three';
import styled from 'styled-components';

interface MiniGame {
    id: string;
    name: string;
    emoji: string;
    description: string;
    color: string;
    available: boolean;
}

const MINI_GAMES: MiniGame[] = [
    {
        id: 'food-catch',
        name: 'Food Catch',
        emoji: '🍕',
        description: 'Let\'s eat a ton of food together !',
        color: '#499dd4',
        available: true,
    },
    {
        id: 'course',
        name: 'Course',
        emoji: '🏁',
        description: 'Let\'s race against your friends!',
        color: '#ae99df',
        available: true,
    },
];

const PageShell = styled.div`
    width: 100%;
    height: 100vh;
    position: relative;
    overflow: hidden;
`;

const SceneCanvas = styled(Canvas)`
    width: 100%;
    height: 100vh;
    background: radial-gradient(circle, #1a1a3e 0%, #0a0a1e 100%);
`;

const Overlay = styled.div`
    position: absolute;
    inset: 0;
    z-index: 1;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: space-between;
    pointer-events: none;
    padding: 30px 20px;

    @media (max-width: 768px) {
        align-items: stretch;
        justify-content: space-between;
        padding: 20px 16px;
    }
`;

const OverlayContent = styled.div`
    text-align: center;
    width: 100%;
    max-width: 1200px;
`;

const Title = styled.h1`
    font-family: 'Press Start 2P', cursive;
    color: white;
    font-size: clamp(1.8rem, 5vw, 2.5rem);
    margin: 0;
    width: 100%;
    text-align: center;
    margin-inline: auto;
    text-shadow: 0 0 10px rgb(255, 255, 255);
    max-width: 900px;
    line-height: 1.1;

    @media (max-width: 768px) {
        font-size: clamp(1.8rem, 7vw, 2.2rem);
        max-width: 18ch;
        margin-inline: auto;
        line-height: 1.25;
    }
`;

const Subtitle = styled.p`
    font-family: 'Nunito, sans-serif';
    color: rgba(255, 255, 255, 0.8);
    margin-top: 20px;
    font-size: clamp(1rem, 2.5vw, 1.1rem);

    @media (max-width: 768px) {
        font-size: clamp(0.95rem, 3vw, 1rem);
    }
`;

const ReturnButton = styled.button`
    pointer-events: auto;
    padding: 14px 40px;
    font-size: clamp(0.95rem, 2.5vw, 1rem);
    font-weight: bold;
    background: rgba(255, 255, 255, 0.1);
    border: 2px solid rgba(255, 255, 255, 0.3);
    border-radius: 50px;
    color: white;
    cursor: pointer;
    transition: all 0.3s ease;
    backdrop-filter: blur(10px);
    min-width: 220px;
    width: auto;

    &:hover {
        background: rgba(255, 255, 255, 0.2);
        border-color: rgba(255, 255, 255, 0.5);
    }

    @media (max-width: 768px) {
        width: 100%;
        max-width: 100%;
        padding: 14px 24px;
    }
`;

const OverlayFooter = styled.div`
    width: 100%;
`;

const LegalLinksContainer = styled.div`
    width: 100%;
    display: flex;
    justify-content: center;
    gap: 16px;
    margin-top: 12px;

    a {
        color: #66ccff;
        text-decoration: none;
        font-size: 0.9rem;

        &:hover {
            color: #ff99cc;
        }
    }
`;

function GlassyGameCube({
    game,
    position,
    scale,
    onSelect,
}: {
    game: MiniGame;
    position: [number, number, number];
    scale: number;
    onSelect: (game: MiniGame) => void;
}) {
    const groupRef = useRef<Group>(null);
    const [hovered, setHovered] = useState(false);

    useFrame((state) => {
        if (groupRef.current) {
            groupRef.current.rotation.y = state.clock.elapsedTime * 0.18;
            groupRef.current.rotation.x = Math.sin(state.clock.elapsedTime * 0.5) * 0.05;
        }
    });

    return (
        <group
            ref={groupRef}
            position={position}
            scale={scale}
            onClick={() => {
                if (game.available) onSelect(game);
            }}
            onPointerOver={() => {
                setHovered(true);
                document.body.style.cursor = game.available ? 'pointer' : 'default';
            }}
            onPointerOut={() => {
                setHovered(false);
                document.body.style.cursor = 'default';
            }}
        >
            <mesh>
                <boxGeometry args={[4.6, 4.4, 2.4]} />
                <meshPhysicalMaterial
                    transparent
                    opacity={0.16}
                    transmission={0.95}
                    thickness={0.35}
                    roughness={0.06}
                    metalness={0}
                    color="#ffffff"
                    emissive={game.color}
                    emissiveIntensity={hovered ? 0.28 : 0.14}
                    clearcoat={1}
                    clearcoatRoughness={0}
                    depthWrite={false}
                    side={THREE.DoubleSide}
                />
            </mesh>

            <lineSegments>
                <edgesGeometry args={[new THREE.BoxGeometry(4.6, 4.4, 2.4)]} />
                <lineBasicMaterial color={game.color} opacity={0.9} transparent />
            </lineSegments>

            <Billboard position={[0, 0, 0]}>
                <Text
                    position={[0, 1, 0]}
                    fontSize={1.5}
                    color="#ffffff"
                    anchorX="center"
                    anchorY="middle"
                    outlineWidth={0.03}
                    outlineColor="#000000"
                >
                    {game.emoji}
                </Text>

                <Text
                    position={[0, -0.4, 0]}
                    fontSize={0.45}
                    color={game.color}
                    anchorX="center"
                    anchorY="middle"
                    fontWeight="bold"
                    outlineWidth={0.025}
                    outlineColor="#000000"
                >
                    {game.name}
                </Text>

                <Text
                    position={[0, -0.9, 0]}
                    fontSize={0.18}
                    color="#ffffff"
                    anchorX="center"
                    anchorY="middle"
                    maxWidth={3.7}
                    textAlign="center"
                    outlineWidth={0.015}
                    outlineColor="#000000"
                >
                    {game.description}
                </Text>

            </Billboard>
        </group>
    );
}

function GameSelectScene({ onSelect, viewportWidth }: { onSelect: (game: MiniGame) => void; viewportWidth: number }) {
    const isSmallTablet = viewportWidth <= 768;
    const isPhone = viewportWidth <= 480;

    const cubeScale = isPhone ? 0.74 : isSmallTablet ? 0.95 : 1;
    const leftCubePosition: [number, number, number] = isPhone ? [-2.55, 0, 0] : isSmallTablet ? [-3.05, 0, 0] : [-3.7, 0, 0];
    const rightCubePosition: [number, number, number] = isPhone ? [2.55, 0, 0] : isSmallTablet ? [3.05, 0, 0] : [3.7, 0, 0];

    return (
        <>
            <ambientLight intensity={0.55} />
            <directionalLight position={[10, 10, 5]} intensity={2.3} />
            <pointLight position={[-9, 6, -8]} intensity={2.6} color="#667eea" />
            <pointLight position={[9, -5, 8]} intensity={2.6} color="#764ba2" />
            <pointLight position={[0, 0, 10]} intensity={2} color="#ff99cc" />

            <Stars radius={100} depth={100} count={8000} factor={6} saturation={50} fade speed={8} />

            <GlassyGameCube
                game={MINI_GAMES[0]}
                position={leftCubePosition}
                scale={cubeScale}
                onSelect={onSelect}
            />
            <GlassyGameCube
                game={MINI_GAMES[1]}
                position={rightCubePosition}
                scale={cubeScale}
                onSelect={onSelect}
            />

            <OrbitControls enableZoom={true} minDistance={5} maxDistance={30} autoRotate={false} autoRotateSpeed={0.5} />
        </>
    );
}

export default function GameSelectPage() {
    const navigate = useNavigate();
    const [viewportWidth, setViewportWidth] = useState(() => window.innerWidth);

    const getCameraPosition = (width: number): [number, number, number] => {
        if (width <= 480) return [0, 0, 30];
        if (width <= 768) return [0, 0, 24];
        return [0, 0, 15];
    };

    const cameraPosition = getCameraPosition(viewportWidth);

    useEffect(() => {
        const updateViewport = () => setViewportWidth(window.innerWidth);
        updateViewport();
        window.addEventListener('resize', updateViewport);
        return () => window.removeEventListener('resize', updateViewport);
    }, []);

    const handleGameSelect = (game: MiniGame) => {
        if (game.available) {
            navigate(`/minigame/${game.id}`);
        }
    };

    return (
        <PageShell>
            <SceneCanvas
                camera={{ position: cameraPosition, fov: 50 }}
                onCreated={({ gl }) => { return () => gl.dispose(); }}
            >
                <GameSelectScene onSelect={handleGameSelect} viewportWidth={viewportWidth} />
            </SceneCanvas>

            <Overlay>
                <OverlayContent>
                    <Title>
                        LET'S RESTORE YOUR NEKOTCHI'S HAPPINESS!
                    </Title>
                    <Subtitle>
                        Select one box to play!
                    </Subtitle>
                </OverlayContent>
                <OverlayFooter>
                <ReturnButton
                    onClick={() => navigate('/nekotchi/me')}
                >
                    ← Let's return to your Nekotchi!
                </ReturnButton>
                <LegalLinksContainer>
                    <Link to="/privacy">Privacy Policy</Link>
                    <Link to="/terms">Terms of Service</Link>
                </LegalLinksContainer>
                </OverlayFooter>
            </Overlay>
        </PageShell>
    );
}
