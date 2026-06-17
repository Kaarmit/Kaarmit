import { useRef, useEffect } from 'react';
import { useGLTF, useAnimations } from '@react-three/drei';
import { Group } from 'three';
import * as THREE from 'three';

interface Props {
  position?: [number, number, number];
  rotation?: [number, number, number];
  scale?: number;
  color?: string;
}

export default function NekotchiModel3D({
  position = [0, 0, 0],
  rotation = [0, 0, 0],
  scale = 1,
  color = '#FF69B4'
}: Props) {
  const group = useRef<Group>(null);

  const { scene, animations } = useGLTF('/3Dmodels/nekotchi3D.glb');

  const { actions, names } = useAnimations(animations, group);

  useEffect(() => {
    if (names.length > 0 && actions[names[0]]) {
      console.log('Animations disponibles:', names);
      actions[names[0]]?.play();
    } else {
      console.log('Aucune animation dans le modèle');
    }
  }, [actions, names]);

  useEffect(() => {
    console.log('=== DEBUG MODÈLE ===');
    console.log('Scene:', scene);

    scene.traverse((child: any) => {
      console.log('Child:', {
        name: child.name,
        type: child.type,
        material: child.material?.type,
        color: child.material?.color,
        visible: child.visible,
      });
    });
  }, [scene]);

  useEffect(() => {
    console.log('=== APPLYING COLOR:', color, '===');

    scene.traverse((child: any) => {
      if (child.isMesh && child.material) {
        if (!child.userData.originalMaterial) {
          child.userData.originalMaterial = child.material;
        }

        child.material = child.userData.originalMaterial.clone();

        if (child.material.color) {
          child.material.color = new THREE.Color(color);
          console.log('Applied color to', child.name);
        }

        if (child.material.emissive !== undefined) {
          child.material.emissive = new THREE.Color(color);
          child.material.emissiveIntensity = 0.2;
        }
      }
    });
  }, [scene, color]);

  return (
    <group ref={group} position={position} rotation={rotation}>
      <primitive
        object={scene}
        scale={scale}
        rotation={[0, Math.PI, 0]}
      />
    </group>
  );
}

useGLTF.preload('/3Dmodels/nekotchi3D.glb');