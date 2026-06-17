import { useNavigate, useParams } from 'react-router-dom';
import { useEffect, useState } from 'react';
import { Canvas } from '@react-three/fiber';
import { OrbitControls, PerspectiveCamera, Environment, ContactShadows } from '@react-three/drei';
import styled from 'styled-components';
import { usePet } from '../context/PetContext';
import { useAuth } from '../hooks/useAuth';
import useFriendsPresence from '../hooks/useFriendsPresence';
import { useFriendPetState } from '../hooks/useFriendPetState';
import NekotchiWithScreen from '../components/Nekotchi3D/NekotchiWithScreen';
import ChatPanel from '../components/Chat/ChatInput';
import FriendsPanel from '../components/Friends/FriendsPanel';
import ProfileCard from '../components/Profile/ProfileCard';
import PetStatsPanel from '../components/Nekotchi3D/PetStatsPanel';
import * as THREE from 'three';
import type { PetAction } from '../types';

const PageContainer = styled.div<{ $backgroundImage: string }>`
  width: 100dvw;
  height: 100dvh;
  min-height: 100svh;
  background-color: #0f0f1e;
  background-image: ${({ $backgroundImage }) =>
    `linear-gradient(rgba(15, 15, 30, 0.38), rgba(15, 15, 30, 0.52)), url(${$backgroundImage})`};
  background-size: cover;
  background-position: center;
  background-repeat: no-repeat;
  overflow: hidden;
  touch-action: none;
`;

const SceneCanvas = styled(Canvas)`
  touch-action: none;
`;

const TitleBar = styled.div`
  position: absolute;
  top: max(12px, env(safe-area-inset-top));
  left: clamp(8px, 3vw, 20px);
  display: flex;
  align-items: center;
  gap: clamp(6px, 3vw, 10px);
  color: white;
  font-size: clamp(1rem, 4vw, 2rem);
  font-weight: bold;
  text-shadow: 2px 2px 8px rgba(0, 0, 0, 0.8);
  padding: clamp(4px, 1.5vw, 10px);
  width: fit-content;
  max-width: calc(100vw - 16px);
  box-sizing: border-box;
  overflow: visible;
  flex-wrap: nowrap;
  z-index: 40;
  pointer-events: none;
`;

const TitleText = styled.span`
  font-family: 'Press Start 2P', cursive;
  font-weight: 500;
  font-size: clamp(1.2rem, 5.8vw, 3rem);
  line-height: 1;
  text-shadow: 0 0 10px white, 0 2px 4px rgba(0, 0, 0, 0.8);
`;

const AvatarButton = styled.button`
  background: transparent;
  border: none;
  padding: 0;
  cursor: pointer;
  pointer-events: auto;
`;

const AvatarImage = styled.img`
  width: 50px;
  height: 50px;
  border-radius: 50%;
  object-fit: cover;
  border: 2px solid rgba(255, 255, 255, 0.65);
  box-shadow: 0 0 12px rgba(255, 255, 255, 0.25);
`;

const AvatarPlaceholder = styled.div`
  width: 50px;
  height: 50px;
  border-radius: 50%;
  border: 2px solid rgba(255, 255, 255, 0.65);
  display: grid;
  place-items: center;
  color: white;
  font-size: 1.4rem;
  background: rgba(255, 255, 255, 0.08);
`;

export default function Nekotchi() {
  const navigate = useNavigate();
  const [friendToOpenId, setFriendToOpenId] = useState<number | null>(null);
  const [friendOpenSignal, setFriendOpenSignal] = useState(0);
  const [avatarLoadError, setAvatarLoadError] = useState(false);
  const [isStatsOpen, setIsStatsOpen] = useState(false);
  const { pet, mood, performAction, color, selectedBackground, catType } = usePet();
  const { user, token, logout } = useAuth();
  const avatarUrl = user?.avatarUrl;
  const username = user?.username;
  const email = user?.email;
  const { userId } = useParams();
  const viewingUserId = userId ? Number(userId) : null;
  const currentUserId = user?.id != null ? Number(user.id) : null;
  const isOwnPet = viewingUserId === null || viewingUserId === currentUserId;
  const [showProfileCard, setShowProfileCard] = useState(false);
  const [viewingUser, setViewingUser] = useState<{ username?: string; avatarUrl?: string } | null>(null);

  const {
    friends,
    onlineCount,
    isConnected: isRealtimeConnected,
    loading: friendsLoading,
    pendingRequests,
    outgoingRequests,
    searchUsers,
    addFriend,
    acceptRequest,
    refuseRequest,
    removeFriend,
  } = useFriendsPresence(token ?? undefined, user?.id != null ? Number(user.id) : undefined);

  // Use new hook to manage friend pet state with socket.io support
  const {
    pet: friendPet,
    catType: friendCatType,
    color: friendColor,
    background: friendBackground,
    loading: friendPetLoading,
    error: friendPetError,
  } = useFriendPetState(viewingUserId);

  const activePet = isOwnPet ? pet : friendPet ?? pet;
  const activeColor = isOwnPet ? color : friendColor;
  const activeCatType = isOwnPet ? catType : friendCatType;
  const activeBackground = isOwnPet ? selectedBackground : friendBackground;

  const handleLogout = async () => {
    await logout();
    navigate('/login', { replace: true });
  };

  // Function to open the chat panel for a specific friend
  const handleOpenFriendChat = (friendId: number) => {
    setFriendToOpenId(friendId);
    setFriendOpenSignal((prev) => prev + 1);
  };

  // After updating profile picture, we want to reset the avatar load error state so that it tries to load the new URL (in case the previous error was due to a broken URL that has now been fixed).
  useEffect(() => {
    setAvatarLoadError(false);
  }, [user?.avatarUrl]);

  useEffect(() => {
    if (isOwnPet || !viewingUserId) {
      setViewingUser(null);
      return;
    }

    const friend = friends.find((f) => f.id === viewingUserId);
    if (friend) {
      setViewingUser({ username: friend.username, avatarUrl: friend.avatarUrl });
    } else {
      setViewingUser(null);
    }
  }, [isOwnPet, viewingUserId, friends]);

  // JSX rendering, including the 3D canvas, title, profile card, pet stats panel, friends panel, and chat panel.
  return (
    // Fullscreen background container
    <PageContainer $backgroundImage={activeBackground}>
      <SceneCanvas
        shadows
        gl={{ antialias: true, toneMapping: THREE.ACESFilmicToneMapping }}
        onCreated={({ gl }) => {
          gl.domElement.style.touchAction = 'none';
          return () => gl.dispose();
        }}
        >
        <PerspectiveCamera makeDefault position={[0, 0, 13]} fov={50} />


        <ambientLight intensity={0.8} />
        <directionalLight position={[5, 10, 5]} intensity={2} castShadow />
        <pointLight position={[-5, 3, -5]} intensity={1.5} color="#667eea" />
        <pointLight position={[5, 3, -5]} intensity={1.5} color="#764ba2" />
        <pointLight position={[0, -2, 5]} intensity={1} color="#ffffff" />
        <spotLight position={[0, 10, 0]} angle={0.5} intensity={1.5} castShadow />

        <Environment preset="city" />

        <NekotchiWithScreen
          pet={activePet}
          color={activeColor}
          mood={mood}
          catType={activeCatType}
          onAction={(action: PetAction) => {
            // When viewing another user's Nekotchi, all interactions are read-only.
            if (!isOwnPet) return;
            if (action === 'play') {
              navigate('/games');
            } else {
              performAction(action);
            }
          }}
        />

        <ContactShadows
          position={[5, -0.5, 25]}
          opacity={0.5}
          scale={10}
          blur={2}
          far={4}
        />

        <OrbitControls
          makeDefault
          enableZoom={true}
          enablePan={false}
          maxDistance={200}
          minDistance={5}
          autoRotate={false}
          touches={{ ONE: THREE.TOUCH.ROTATE, TWO: THREE.TOUCH.DOLLY_ROTATE }}
        />
      </SceneCanvas>

      <TitleBar>
        <TitleText>
          NEKOTCHI
        </TitleText>
        {user?.avatarUrl && !avatarLoadError ? (
          <AvatarButton
            onClick={() => setShowProfileCard(s => !s)}
            aria-expanded={showProfileCard}
            aria-controls="profile-card"
          >
            <AvatarImage
              src={user.avatarUrl}
              alt="Avatar utilisateur"
              onError={() => setAvatarLoadError(true)}
            />
          <ProfileCard
            forceOpen={showProfileCard}
            avatarUrl={avatarUrl}
            username={username || ''}
            email={email || ''}
            onEditClick={() => navigate('/edit-profile')}
          />
          </AvatarButton>
        ) : (
          <AvatarPlaceholder>
            👤
          </AvatarPlaceholder>
        )}
      </TitleBar>

      <PetStatsPanel
        activePet={activePet}
        mood={mood}
        isOwnPet={isOwnPet}
        isStatsOpen={isStatsOpen}
        onToggleStats={() => setIsStatsOpen((prev) => !prev)}
        viewingPetLoading={friendPetLoading}
        viewingPetError={friendPetError}
        viewingUser={viewingUser}
        onLogout={handleLogout}
        onReturnToMyPet={() => navigate('/nekotchi/me')}
      />
      
      {isOwnPet && (
        <FriendsPanel
        friends={friends}
        onlineCount={onlineCount}
        isRealtimeConnected={isRealtimeConnected}
        loading={friendsLoading}
        pendingRequests={pendingRequests}
        outgoingRequests={outgoingRequests}
        searchUsers={searchUsers}
        addFriend={addFriend}
        refuseRequest={refuseRequest}
        acceptRequest={acceptRequest}
        removeFriend={removeFriend}
        openChatWithFriend={handleOpenFriendChat}
        />
      )}

      <ChatPanel
        friends={friends}
        friendToOpenId={friendToOpenId}
        friendToOpenSignal={friendOpenSignal}
        currentUserId={user?.id}
        currentUsername={user?.username}
      />
    </PageContainer>

  );
}