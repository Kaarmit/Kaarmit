import { RoundedBox, Text } from '@react-three/drei';
import type { PetMood, PetState, CatType, PetAction } from '../../types';
import Cat3D from './Cat3D';
import { useFrame } from '@react-three/fiber';
import { useRef, useState } from 'react';
import type { Mesh, Group } from 'three';
import { useLoader } from '@react-three/fiber';
import { TextureLoader } from 'three';

interface Props {
  position: [number, number, number];
  pet: PetState;
  mood?: PetMood;
  catType?: CatType;
  color?: string;
  overrideSprite?: string;
  onAction: (action: PetAction) => void;
}

export default function FloatingScreen({
  position,
  mood,
  catType = 'beigecat',
  color = '#FFFFFF',
  overrideSprite,
  onAction,
}: Props) {

  type ActionButton = {
    action: PetAction;
    icon: string;
    label: string;
    position: [number, number, number];
    rotation: [number, number, number];
    labelOffset: number;
  };

  const actionButtons: ActionButton[] = [
    { action: 'feed', icon: '/icons/feed.png', label: 'Feed', position: [-1.27, -1.85, -0.17], rotation: [Math.PI / 12, 0, 0], labelOffset: 0.20 },
    { action: 'play', icon: '/icons/play.png', label: 'Play', position: [-0.65, -2.05, -0.11], rotation: [Math.PI / 12, 0, 0], labelOffset: 0.20 },
    { action: 'cuddle', icon: '/icons/cuddle.png', label: 'Cuddle', position: [0, -2.2, -0.1], rotation: [Math.PI / 12, 0, 0], labelOffset: 0.20 },
    { action: 'clean', icon: '/icons/clean.png', label: 'Clean', position: [0.65, -2.08, -0.12], rotation: [Math.PI / 12, 0, 0], labelOffset: 0.20 },
    { action: 'sleep', icon: '/icons/sleep.png', label: 'Sleep', position: [1.26, -1.85, -0.18], rotation: [Math.PI / 12, 0, 0], labelOffset: 0.20 },
  ];

  const iconTextures = useLoader(
    TextureLoader,
    actionButtons.map(btn => btn.icon)
  );

  const [hoveredIndex, setHoveredIndex] = useState<number | null>(null);

  return (
    <group position={position} rotation={[0, 0, 0]}>
      {/* Ecran noir */}
      <RoundedBox
        args={[2.5, 2.5, 0.2]}
        radius={0.15}
        smoothness={4}
        position={[0, 0, 0.1]}
      >
        <meshStandardMaterial
          color="#0a0a1e"
          roughness={0.2}
          metalness={0.8}
          emissive="#1a1a3e"
          emissiveIntensity={0.5}
        />
      </RoundedBox>

      <RoundedBox
        args={[2.7, 2.7, 0.08]}
        radius={0.2}
        smoothness={4}
        position={[0, 0, -0.1]}
      >
        <meshStandardMaterial
          color="#667eea"
          roughness={0.3}
          metalness={0.5}
        />
      </RoundedBox>

      <group rotation={[0, Math.PI, 0]}>
        <Cat3D
          position={[0, -0.1, -0.21]}
          scale={1.4}
          mood={mood}
          catType={catType}
          color={color}
          overrideSprite={overrideSprite}
        />
      </group>

      {mood === 'asleep' && <SleepingZzzz />}

      {actionButtons.map((btn, i) => (
        <>
          <mesh
            key={btn.action}
            position={btn.position}
            rotation={btn.rotation}
            onClick={() => onAction(btn.action)}
            onPointerOver={() => setHoveredIndex(i)}
            onPointerOut={() => setHoveredIndex(null)}
          >
            <planeGeometry args={[0.32, 0.32]} />
            <meshBasicMaterial 
              map={iconTextures[i]} 
              transparent
            />
          </mesh>
          {hoveredIndex === i && (
            <Text
              position={[btn.position[0], btn.position[1] + btn.labelOffset, btn.position[2] + 0.2]}
              fontSize={0.12}
              font="/fonts/PressStart2P-Regular.ttf"
              color="#fff"
              anchorX="center"
              anchorY="bottom"
            >
              {btn.label}
            </Text>
          )}
        </>
      ))}

    </group>
  );
}

function SleepingZzzz() {
  const groupRef = useRef<Group>(null);
  const textRef = useRef<Mesh>(null);

  useFrame(({ clock }) => {
    const t = clock.getElapsedTime();

    if (groupRef.current) {
      groupRef.current.position.x = Math.sin(t * 2) * 0.2;
    }

    if (textRef.current) {
      textRef.current.rotation.z = Math.sin(t * 1.5) * 0.15;
    }
  });

  return (
    <group ref={groupRef} position={[0.6, 0.8, 0.25]}>
      <Text
        ref={textRef}
        fontSize={0.35}
        color="#bcd4ff"
        anchorX="center"
        anchorY={0.3}
        outlineWidth={0.01}
        outlineColor="#1a1a3e"
        rotation={[0, 0, 0]}
      >
        Z z z
      </Text>
    </group>
  );
}