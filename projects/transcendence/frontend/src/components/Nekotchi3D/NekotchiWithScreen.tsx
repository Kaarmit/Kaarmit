import { useRef } from 'react';
import { useFrame } from '@react-three/fiber';
import { Group } from 'three';
import NekotchiModel3D from './NekotchiModel3D';
import FloatingScreen from './NekotchiFloatingScreen';
import type { PetMood, PetState, CatType, PetAction } from '../../types';

interface Props {
    pet: PetState;
    color?: string;
    mood?: PetMood;
    catType?: CatType;
    overrideSprite?: string;
    showEgg?: boolean;
    position?: [number, number, number];
    onAction: (action: PetAction) => void;
}

export default function NekotchiWithScreen({ pet, color = '#FF69B4', mood, catType = 'beigecat', overrideSprite, showEgg = false, position = [0, 0, 0], onAction }: Props) {
    const containerRef = useRef<Group>(null);

    useFrame((state) => {
        if (containerRef.current) {
            containerRef.current.rotation.y = Math.sin(state.clock.elapsedTime * 0.3) * 0.2;
        }
    });

    return (
        <group ref={containerRef} position={position} rotation={[0, 0, 0]}>
            {showEgg ? (
                <group position={[0, 0, 0]}>
                    <mesh castShadow receiveShadow position={[0, -0.5, 0]} scale={[2.5, 2.5, 2.5]}>
                        <sphereGeometry args={[1, 48, 48]} />
                        <meshStandardMaterial color={0xf7f3e6} roughness={0.6} metalness={0.05} />
                    </mesh>
                </group>
            ) : (
                <NekotchiModel3D
                    position={[0, 0, 0]}
                    rotation={[0, 0, 0]}
                    scale={2.5}
                    color={color}
                />
            )}

            <FloatingScreen
                position={[0, 0.28, 1.55]}
                pet={pet}
                mood={mood}
                catType={catType}
                overrideSprite={overrideSprite}
                color={color}
                onAction={onAction}
            />
        </group>
    );
}