import { useEffect, useMemo, useRef } from 'react';
import { useFrame } from '@react-three/fiber';
import { useTexture } from '@react-three/drei';
import { ClampToEdgeWrapping, DoubleSide, Group, NearestFilter, RepeatWrapping, Texture } from 'three';
import type { PetMood, CatType } from '../../types';

const spritesByCat: Record<CatType, Record<PetMood, string>> = {
  beigecat: {
    idle: 'idle.png',
    happy: 'excited.png',
    sad: 'cry.png',
    eating: 'eat.png',
    asleep: 'asleep.png',
    sleepy: 'sleepy.png',
    hungry: 'angry.png',
    dead: 'dead.png',
    dirty: 'bored.png',
    clean: 'bath.png',
    bored: 'bored.png',
    laughing: 'laugh.png',
    shy: 'shy.png',
    no: 'no.png',
  },
  greycat: {
    idle: 'idle.png',
    happy: 'excited.png',
    sad: 'cry.png',
    eating: 'eat.png',
    asleep: 'asleep.png',
    sleepy: 'sleepy.png',
    hungry: 'angry.png',
    dead: 'dead.png',
    dirty: 'bored.png',
    clean: 'bath.png',
    bored: 'bored.png',
    laughing: 'laugh.png',
    shy: 'shy.png',
    no: 'no.png',
  },
  orangecat: {
    idle: 'idle.png',
    happy: 'excited.png',
    sad: 'cry.png',
    eating: 'eat.png',
    asleep: 'asleep.png',
    sleepy: 'sleepy.png',
    hungry: 'angry.png',
    dead: 'dead.png',
    dirty: 'bored.png',
    clean: 'bath.png',
    bored: 'bored.png',
    laughing: 'laugh.png',
    shy: 'shy.png',
    no: 'no.png',
  },
  whitecat: {
    idle: 'idle.png',
    happy: 'excited.png',
    sad: 'sad.png',
    eating: 'eat.png',
    asleep: 'asleep.png',
    sleepy: 'sleepy.png',
    hungry: 'no.png',
    dead: 'dead.png',
    dirty: 'bored.png',
    clean: 'bath.png',
    bored: 'bored.png',
    laughing: 'laugh.png',
    shy: 'shy.png',
    no: 'no.png',
  },
};

const DEFAULT_ATLAS_STRIDE = 32;
const CLEAN_ATLAS = {
  frameWidth: 60,
  startX: 0,
  stride: 64,
  frameCount: 6,
};

interface Props {
  position: [number, number, number];
  scale: number;
  mood?: PetMood;
  catType?: CatType;
  color?: string;
  overrideSprite?: string;
}

export default function Cat3D({ position, scale, mood = 'idle', catType = 'beigecat', color = '#FFFFFF', overrideSprite }: Props) {
  const group = useRef<Group>(null);
  const startTimeRef = useRef(0);

  const spritesheetsPaths = useMemo(() => {
    const basePath = `/${catType}`;
    return {
      idle: `${basePath}/${spritesByCat[catType].idle}`,
      happy: `${basePath}/${spritesByCat[catType].happy}`,
      sad: `${basePath}/${spritesByCat[catType].sad}`,
      eating: `${basePath}/${spritesByCat[catType].eating}`,
      asleep: `${basePath}/${spritesByCat[catType].asleep}`,
      sleepy: `${basePath}/${spritesByCat[catType].sleepy}`,
      hungry: `${basePath}/${spritesByCat[catType].hungry}`,
      dead: `${basePath}/${spritesByCat[catType].dead}`,
      dirty: `${basePath}/${spritesByCat[catType].dirty}`,
      clean: `${basePath}/${spritesByCat[catType].clean}`,
      // clean: getBathSpritePath(color),
      bored: `${basePath}/${spritesByCat[catType].bored}`,
      laughing: `${basePath}/${spritesByCat[catType].laughing}`,
      shy: `${basePath}/${spritesByCat[catType].shy}`,
      no: `${basePath}/${spritesByCat[catType].no}`,
    };
  }, [catType, color]);

  const textures = useTexture(spritesheetsPaths);

  const overrideTexture = overrideSprite ? useTexture(overrideSprite) : undefined;

  const moodToTexture: Record<NonNullable<Props['mood']>, Texture> = {
    idle: textures.idle,
    happy: textures.happy,
    sad: textures.sad,
    eating: textures.eating,
    asleep: textures.asleep,
    sleepy: textures.sleepy,
    hungry: textures.hungry,
    dead: textures.dead,
    dirty: textures.dirty,
    clean: textures.clean,
    bored: textures.bored,
    laughing: textures.laughing,
    shy: textures.shy,
    no: textures.no,
  }

  const activeTexture: Texture = (overrideTexture as any) ?? moodToTexture[mood ?? 'idle'];
  const catTypeScaleFactor = 1;

  const getAtlas = (currentMood: PetMood, imageWidth: number) => {
    if (currentMood === 'clean') {
      const requiredWidth = CLEAN_ATLAS.startX + CLEAN_ATLAS.stride * (CLEAN_ATLAS.frameCount - 1) + CLEAN_ATLAS.frameWidth;
      if (imageWidth >= requiredWidth) {
        return CLEAN_ATLAS;
      }

      const cleanFrameCount = 7;
      const cleanFrameWidth = Math.max(1, Math.floor(imageWidth / cleanFrameCount));
      return {
        frameWidth: cleanFrameWidth,
        startX: 0,
        stride: cleanFrameWidth,
        frameCount: cleanFrameCount,
      };
    }

    return {
      frameWidth: DEFAULT_ATLAS_STRIDE,
      startX: 0,
      stride: DEFAULT_ATLAS_STRIDE,
      frameCount: Math.max(1, Math.floor(imageWidth / DEFAULT_ATLAS_STRIDE)),
    };
  };

  // cut the sprite sheet into frames and set texture parameters
  useEffect(() => {
    if (!activeTexture.image)
      return;

    const image = activeTexture.image as { width: number; height: number };
    const currentMood = mood ?? 'idle';
    const atlas = getAtlas(currentMood, image.width);
    const frameWidthRatio = atlas.frameWidth / image.width;
    const initialOffsetX = atlas.startX / image.width;

    activeTexture.magFilter = NearestFilter;
    activeTexture.minFilter = NearestFilter;
    activeTexture.wrapS = currentMood === 'clean' ? ClampToEdgeWrapping : RepeatWrapping;
    activeTexture.repeat.set(frameWidthRatio, 1);
    activeTexture.offset.set(initialOffsetX, 0);
    activeTexture.generateMipmaps = false;
    activeTexture.needsUpdate = true;
  }, [activeTexture, mood, catType]);

  useEffect(() => {
    startTimeRef.current = -1;
  }, [mood]);

  useFrame((state) => {
    if (startTimeRef.current < 0) {
      startTimeRef.current = state.clock.elapsedTime;
    }

    if (activeTexture.image) {
      const image = activeTexture.image as { width: number; height: number };
      const currentMood = mood ?? 'idle';
      const atlas = getAtlas(currentMood, image.width);
      const frameCount = atlas.frameCount;
      const fpsByMood: Record<NonNullable<Props['mood']>, number> = {
        idle: 3,
        happy: 6,
        sad: 1,
        eating: 6,
        asleep: 3,
        sleepy: 4,
        hungry: 4,
        dead: 2,
        dirty: 4,
        clean: 6,
        bored: 4,
        laughing: 6,
        shy: 4,
        no: 4,
      };

      const fps = fpsByMood[currentMood];
      if (fps <= 0) {
        activeTexture.offset.x = atlas.startX / image.width;
        return;
      }
      const frameDuration = 1 / fps;
      const elapsed = state.clock.elapsedTime - startTimeRef.current;
      const currentFrame = Math.floor(elapsed / frameDuration) % frameCount;

      activeTexture.offset.x = (atlas.startX + currentFrame * atlas.stride) / image.width;
    }

    if (group.current) {
      group.current.position.x = position[0] + Math.sin(state.clock.elapsedTime * 0.7) * 0.03;
      group.current.position.y = position[1] + Math.sin(state.clock.elapsedTime * 1.8) * 0.015;
      group.current.rotation.z = Math.sin(state.clock.elapsedTime * 0.8) * 0.01;
      group.current.scale.set(scale, scale, scale);
    }
  });


  return (
    <group ref={group} position={position}>
      <mesh scale={[scale * catTypeScaleFactor, scale * catTypeScaleFactor, 1]}>
        <planeGeometry args={[1, 1]} />
        <meshBasicMaterial map={activeTexture} transparent alphaTest={0.1} depthWrite={false} side={DoubleSide} />
      </mesh>
    </group>
  );
}