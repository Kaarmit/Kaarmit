import { useEffect } from 'react';
import { useLocation, useNavigate, Link } from 'react-router-dom';
import { Canvas } from '@react-three/fiber';
import { OrbitControls, PerspectiveCamera, Environment } from '@react-three/drei';
import styled from 'styled-components';
import { usePet } from '../context/PetContext';
import NekotchiWithScreen from '../components/Nekotchi3D/NekotchiWithScreen';
import * as THREE from 'three';
import CustomizationFlow from '../components/Customize/CustomizationFlow';
import { ContactShadows } from '@react-three/drei';
import { DEFAULT_CAT_TYPE, DEFAULT_PET_BACKGROUND, DEFAULT_PET_COLOR, DEFAULT_PET_STATE } from '../context/PetContext';

const PageShell = styled.div<{ $backgroundImage: string }>`
  width: 100vw;
  height: 100vh;
  background-color: #0f0f1e;
  background-image: ${({ $backgroundImage }) =>
    `linear-gradient(rgba(15, 15, 30, 0.38), rgba(15, 15, 30, 0.52)), url(${$backgroundImage})`};
  background-size: cover;
  background-position: center;
  background-repeat: no-repeat;
`;

const SceneCanvas = styled(Canvas)`
  position: absolute;
  inset: 0;
`;

const FlowOverlay = styled.div`
  position: absolute;
  inset: 0;
  display: flex;
  align-items: flex-start;
  justify-content: center;
  pointer-events: none;
  padding-top: 14vh;
  z-index: 6;
`;

const FlowFrame = styled.div`
  pointer-events: auto;
  z-index: 7;
  width: 100%;
  max-width: 820px;
  margin: 0 auto;
`;

const TitleLayer = styled.div`
  position: absolute;
  inset: 0;
  z-index: 1;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between;
  pointer-events: none;
  padding: 30px 20px;
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
  z-index: 6;

  a {
    color: #66ccff;
    text-decoration: none;
    font-size: 0.875rem;
    transition: color 0.2s ease;

    &:hover {
      color: #ff99cc;
    }
  }

  @media (max-width: 480px) {
    gap: 12px;
    padding: 8px;
    font-size: 0.75rem;
    bottom: 8px;
  }
`;

const TitleCenter = styled.div`
  text-align: center;
`;

const Title = styled.h1`
  font-family: 'Press Start 2P', cursive;
  font-weight: 700;
  color: white;
  font-size: clamp(1.1rem, 5.5vw, 2.5rem);
  text-shadow: 0 0 10px rgb(255, 255, 255);
`;

export default function CustomizePage() {
  const navigate = useNavigate();
  const location = useLocation();
  const { pet, color, selectedBackground, catType, resetToDefaults } = usePet();

  const resetCustomization = Boolean((location.state as { resetCustomization?: boolean } | null)?.resetCustomization);

  useEffect(() => {
    if (!resetCustomization) {
      return;
    }

    localStorage.removeItem('nekotchi-custom');
    resetToDefaults();
    navigate(location.pathname, { replace: true, state: null });
  }, [location.pathname, location.state, navigate, resetCustomization, resetToDefaults]);

  const previewPet = resetCustomization ? DEFAULT_PET_STATE : pet;
  const previewColor = resetCustomization ? DEFAULT_PET_COLOR : color;
  const previewBackground = resetCustomization ? DEFAULT_PET_BACKGROUND : selectedBackground;
  const previewCatType = resetCustomization ? DEFAULT_CAT_TYPE : catType;

  return (
    <PageShell $backgroundImage={previewBackground}>
      <SceneCanvas shadows gl={{ antialias: true, toneMapping: THREE.ACESFilmicToneMapping }} onCreated={({ gl }) => { return () => gl.dispose(); }}>
        <PerspectiveCamera makeDefault position={[0, 0, 20]} fov={50} />

        {/* Lights */}
        <ambientLight intensity={0.8} />
        <directionalLight position={[5, 10, 5]} intensity={2} castShadow />
        <pointLight position={[-5, 3, -5]} intensity={1.5} color="#667eea" />
        <pointLight position={[5, 3, -5]} intensity={1.5} color="#764ba2" />
        <pointLight position={[0, -2, 5]} intensity={1} color="#ffffff" />
        <spotLight position={[0, 10, 0]} angle={0.5} intensity={1.5} castShadow />

        <Environment preset="city" />

        <NekotchiWithScreen pet={previewPet} color={previewColor} catType={previewCatType} overrideSprite={`/${previewCatType}/box.png`} position={[0, -2.5, 0]} onAction={() => {}} />

        <ContactShadows
          position={[5, -0.5, 25]}
          opacity={0.5}
          scale={10}
          blur={2}
          far={4}
        />

        <OrbitControls
          enableZoom={false}
          maxDistance={200}
          minDistance={5}
          enableRotate={false}
          autoRotate={false}
        />
      </SceneCanvas>

      <FlowOverlay>
        <FlowFrame>
          <CustomizationFlow />
        </FlowFrame>
      </FlowOverlay>

      <TitleLayer>
        <TitleCenter>
          <Title>
            LET'S CUSTOMIZE YOUR NEKOTCHI
          </Title>
        </TitleCenter>
      </TitleLayer>
      <LegalLinksContainer>
        <Link to="/privacy">Privacy Policy</Link>
        <Link to="/terms">Terms of Service</Link>
      </LegalLinksContainer>
    </PageShell>
  );
}