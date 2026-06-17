import styled from 'styled-components';
import { Canvas } from "@react-three/fiber";
import { Stars, Environment, MeshReflectorMaterial } from "@react-three/drei";

const StyledCanvas = styled(Canvas)`
  height: 100vh;
  background: radial-gradient(circle, #1a1a3e 0%, #0a0a1e 100%);
`;

function ReflectiveFloor() {
    return (
        <mesh rotation={[-Math.PI / 2, 0, 0]} position={[0, -3.25, 0]} receiveShadow>
            <planeGeometry args={[40, 40]} />
            <MeshReflectorMaterial
                blur={[400, 200]}
                resolution={256}
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

function SceneContent() {
    return (
        <>
            <fog attach="fog" args={["#532b4d", 12, 35]} />
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
                count={500}
                factor={6}
                saturation={50}
                fade={true}
                speed={1}
            />

            <ReflectiveFloor />
        </>
    );
}

type FormEnvironmentProps = {
    cameraPosition?: [number, number, number];
};

export default function FormEnvironment({ cameraPosition = [0, 0, 16] }: FormEnvironmentProps) {
    return (
        <StyledCanvas
            camera={{ position: cameraPosition, fov: 40 }}
            // shadows
            dpr={[1, 1.2]}
            gl={{ antialias: true, powerPreference: "high-performance" }}
            onCreated={({ gl }) => { return () => gl.dispose(); }}
        >
            <SceneContent />
        </StyledCanvas>
    );
}