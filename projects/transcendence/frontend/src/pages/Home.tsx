import styled from "styled-components";
import { Canvas } from "@react-three/fiber";
import { OrbitControls, Stars, Environment, Sparkles, Float, MeshReflectorMaterial, Text, RoundedBox } from "@react-three/drei";
import { useNavigate, Link } from "react-router-dom";
import { useRef, useState, useEffect } from "react";
import { Group } from "three";
import * as THREE from "three";

const HomeContainer = styled.div`
  position: relative;
  width: 100%;
  height: 100vh;
  overflow: hidden;
`;

const StyledCanvas = styled(Canvas)`
  height: 100vh;
  width: 100%;
  background: radial-gradient(circle, #1a1a3e 0%, #0a0a1e 100%);
`;

const LegalLinksContainer = styled.footer`
  position: absolute;
  bottom: 16px;
  left: 0;
  right: 0;
  width: 100%;
  padding: 16px;
  display: flex;
  justify-content: center;
  gap: 24px;
  flex-wrap: wrap;
  
  a {
    color: #0066cc;
    text-decoration: none;
    font-size: 0.875rem;
    transition: color 0.2s ease;
    
    &:hover {
      color: #0052a3;
    }
  }

  @media (max-width: 768px) {
    gap: 16px;
    padding: 12px;
    font-size: 0.75rem;
    
    a {
      font-size: 0.75rem;
    }
  }

  @media (max-width: 480px) {
    gap: 12px;
    padding: 8px;
    font-size: 0.65rem;
    bottom: 8px;
    
    a {
      font-size: 0.65rem;
    }
  }
`;

interface MenuItemProps {
    position: [number, number, number];
    text: string;
    onClick: () => void;
    color?: string;
    hoverColor?: string;
    font?: string;
    scale?: number;
}

function MenuItem({ position, text, onClick, color = "#ffffff", hoverColor = "#66ccff", font, scale = 1 }: MenuItemProps) {
    const [hovered, setHovered] = useState(false);
    const activeColor = hovered ? hoverColor : color;
    const oppositeColor = hovered ? color : hoverColor;

    return (
        <group
            position={position}
            onClick={onClick}
            onPointerOver={(e) => {
                e.stopPropagation();
                setHovered(true);
                document.body.style.cursor = "pointer";
            }}
            onPointerOut={(e) => {
                e.stopPropagation();
                setHovered(false);
                document.body.style.cursor = "default";
            }}
        >
            <RoundedBox args={[2.35 * scale, 0.41 * scale, 0.1]} radius={0.095 * scale} smoothness={4}>
                <meshBasicMaterial
                    color={activeColor}
                    transparent
                    opacity={1}
                />
            </RoundedBox>

            <Text
                position={[0, 0, 0.08]}
                fontSize={0.25 * scale}
                color={oppositeColor}
                anchorX="center"
                anchorY="middle"
                fontWeight={900}
                outlineWidth={0.014 * scale}
                outlineColor="#000000"
                font={font}
            >
                {text}
            </Text>
        </group>
    );
}

function GlassyEgg({ eggScale = 1 }: { eggScale?: number }) {
    const navigate = useNavigate();
    const groupRef = useRef<Group>(null);

    return (
        <Float speed={65} rotationIntensity={0.5} floatIntensity={0.2}>
            <group ref={groupRef} position={[0, 0.5 * eggScale, 0]}>
                <mesh castShadow receiveShadow scale={[1.1 * eggScale, 1.24 * eggScale, 0.92 * eggScale]}>
                    {/* elongated sphere */}
                    <sphereGeometry args={[2.4, 18, 20]} />
                    <meshPhysicalMaterial
                        transparent
                        opacity={1}
                        transmission={0.99}
                        thickness={0.8}
                        roughness={0.04}
                        metalness={0.08}
                        color="#081216"
                        emissive="#848fbe"
                        emissiveIntensity={0.1}
                        clearcoat={1}
                        clearcoatRoughness={0}
                        iridescence={0.5}
                        iridescenceIOR={1.3}
                        attenuationColor="#aa10af"
                        attenuationDistance={1.8}
                        depthWrite={false}
                        side={THREE.DoubleSide}
                    />
                </mesh>
                
                <group>
                    <Text
                        font="/fonts/PressStart2P-Regular.ttf"
                        position={[0, 0.9 * eggScale, 0]}
                        fontSize={0.55 * eggScale}
                        color="#ff99cc"
                        anchorX="center"
                        anchorY="middle"
                        fontWeight="bold"
                        outlineWidth={0.035 * eggScale}
                        outlineColor="#66ccff"
                    >
                        NEKOTCHI
                    </Text>

                    <Text
                        font="/fonts/PressStart2P-Regular.ttf"
                        position={[0, -0.18 * eggScale, 0]}
                        fontSize={0.14 * eggScale}
                        color="#ffffff"
                        anchorX="center"
                        anchorY="middle"
                        maxWidth={4 * eggScale}
                        textAlign="center"
                        lineHeight={1.5}
                    >
                        ✦ Take care of your virtual pet and connect with your friends ✦
                    </Text>

                    <MenuItem
                        position={[0, -0.95 * eggScale, 0]}
                        text=" START PLAYING "
                        onClick={() => navigate("/login")}
                        color="#66ccff"
                        hoverColor="#ff99cc"
                        scale={eggScale}
                    />

                    <MenuItem
                        position={[0, -1.57 * eggScale, 0]}
                        text="REGISTER"
                        onClick={() => navigate("/register")}
                        color="#ff99cc"
                        scale={eggScale}
                    />
                </group>
            </group>
        </Float>
    );
}

function ReflectiveFloor() {
    return (
        <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, -3.25, 0]} receiveShadow>
            <planeGeometry args={[100, 100]} />
            <MeshReflectorMaterial
                blur={[400, 200]}
                resolution={1024}
                mixBlur={7}
                mixStrength={22}
                roughness={0.35}
                depthScale={0.35}
                minDepthThreshold={0.4}
                maxDepthThreshold={1.2}
                color="#a75d9d"
                metalness={0.6}
                mirror={0.8}
            />
        </mesh>
    );
}

function SceneContent({ eggScale = 1 }: { eggScale?: number }) {
    return (
        <>
            <fog attach="fog" args={["#532b4d", 12, 70]} />

            <ambientLight intensity={50} />
            <directionalLight
                position={[9, 11, 4]}
                intensity={6}
                castShadow
                shadow-mapSize-width={1024}
                shadow-mapSize-height={1024}
            />

            <Environment preset="dawn" />

            <Stars
                radius={100}
                depth={100}
                count={8000}
                factor={6}
                saturation={50}
                fade={true}
                speed={10}
            />

            <Sparkles
                count={80}
                scale={[16, 8, 16]}
                size={5}
                speed={0.5}
                opacity={0.6}
                color="#ac52a0"
            />

            <ReflectiveFloor />

            <GlassyEgg eggScale={eggScale} />

            <OrbitControls
                enableZoom={true}
                minDistance={30}
                maxDistance={45}
                autoRotate={true}
                autoRotateSpeed={0.06}
                minPolarAngle={0}
                maxPolarAngle={Math.PI / 2}
            />
        </>
    );
}

export default function Home() {
    const [eggScale, setEggScale] = useState(1);

    useEffect(() => {
        function updateScale() {
            const w = window.innerWidth;
            if (w <= 480) setEggScale(0.85);
            else if (w <= 768) setEggScale(0.85);
            else setEggScale(1.15);
        }

        updateScale();
        window.addEventListener("resize", updateScale);
        return () => window.removeEventListener("resize", updateScale);
    }, []);
    return (
        <HomeContainer>
            <StyledCanvas
                camera={{ position: [0, 0, 30], fov: 19 }}
                shadows
                dpr={[1, 1]}
                gl={{ antialias: true, powerPreference: "high-performance" }}
                onCreated={({ gl }) => { return () => gl.dispose(); }}
            >
                <SceneContent eggScale={eggScale} />
            </StyledCanvas>
            <LegalLinksContainer>
                <Link to="/privacy">Privacy Policy</Link>
                <Link to="/terms">Terms of Service</Link>
            </LegalLinksContainer>
        </HomeContainer>
    );
}