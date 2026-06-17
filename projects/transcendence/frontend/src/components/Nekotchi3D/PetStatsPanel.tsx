import type { PetMood, PetState } from '../../types';
import styled from 'styled-components';
import ToggleButton from '../ToggleButton';

const StatItem = styled.div`
  margin-bottom: 12px;
`;

const StatLabel = styled.span`
  font-family: 'Nunito, sans-serif';
  font-weight: 700;
  color: white;
  font-size: 0.9rem;
`;

const StatRowLine = styled.div`
  display: flex;
  align-items: center;
  gap: 8px;
  margin-top: 4px;
`;

const GaugeTrack = styled.div`
  flex: 1;
  height: 10px;
  background: rgba(255, 255, 255, 0.1);
  border-radius: 5px;
  overflow: hidden;
  box-shadow: 0 0 5px grey;
`;

const GaugeFill = styled.div<{ $color: string; $value: number }>`
  width: ${({ $value }) => `${$value}%`};
  height: 100%;
  background: ${({ $color }) => $color};
  transition: all 0.5s ease;
`;

const StatValue = styled.span<{ $color: string }>`
  color: ${({ $color }) => $color};
  font-family: 'Press Start 2P', cursive;
  font-size: 0.6rem;
  min-width: 40px;
  text-align: right;
`;

const PanelAnchor = styled.div`
  position: absolute;
  top: clamp(84px, 15vw, 112px);
  left: clamp(8px, 3vw, 20px);
  z-index: 50;
  width: auto;
  max-width: 340px;
  display: flex;
  flex-direction: column;
  box-sizing: border-box;
  align-items: flex-start;
  pointer-events: none;
`;

const ReadOnlyBannerWrap = styled.div`
  position: absolute;
  bottom: max(12px, env(safe-area-inset-top));
  left: 0;
  width: 100%;
  display: flex;
  justify-content: center;
  padding: 0 clamp(8px, 3vw, 16px);
  box-sizing: border-box;
  z-index: 30;
  pointer-events: none;
`;

const ReadOnlyBanner = styled.div`
  width: min(100%, 560px);
  padding: clamp(6px, 1.8vw, 10px) clamp(10px, 2.8vw, 16px);
  border-radius: 999px;
  border: 1px solid rgba(255, 255, 255, 0.35);
  background: rgba(10, 10, 30, 0.82);
  color: #ffd166;
  font-family: 'Nunito, sans-serif';
  font-size: clamp(0.72rem, 2.2vw, 0.92rem);
  font-weight: 700;
  line-height: 1.3;
  backdrop-filter: blur(8px);
  text-align: center;
  white-space: normal;
`;

const StatsCard = styled.div<{ $isOpen: boolean }>`
  margin-top: clamp(8px, 2vw, 10px);
  background: rgba(10, 10, 30, 0.9);
  padding: clamp(12px, 3.2vw, 20px);
  border-radius: clamp(14px, 4vw, 20px);
  border: 2px solid rgba(102, 126, 234, 0.5);
  backdrop-filter: blur(10px);
  width: 100%;
  min-width: 0;
  max-height: 68dvh;
  overflow-y: auto;
  opacity: ${({ $isOpen }) => ($isOpen ? 1 : 0)};
  transform: ${({ $isOpen }) => ($isOpen ? 'translateY(0) scale(1)' : 'translateY(-8px) scale(0.98)')};
  transform-origin: top left;
  transition: opacity 0.2s ease, transform 0.2s ease;
  pointer-events: ${({ $isOpen }) => ($isOpen ? 'auto' : 'none')};
  will-change: transform, opacity;
  padding-bottom: env(safe-area-inset-bottom);
`;

const Title = styled.h2`
  color: white;
  margin: 0 0 clamp(10px, 3vw, 16px) 0;
  font-size: clamp(0.75rem, 2.6vw, 1rem);
  text-align: center;
  font-family: 'Press Start 2P', cursive;
  text-shadow: 0 0 10px white, 0 2px 4px rgba(0, 0, 0, 0.8);
  word-break: break-word;
  overflow: hidden;
  overflow-wrap: break-word;
  text-overflow: ellipsis;
  white-space: nowrap;
`;

const StatusMessage = styled.div`
  margin-bottom: 12px;
  color: #c2c7d3;
  font-family: 'Nunito, sans-serif';
  font-size: 0.85rem;
  text-align: center;
`;

const ErrorMessage = styled.div`
  margin-bottom: 12px;
  color: #ff9fa1;
  font-family: 'Nunito, sans-serif';
  font-size: 0.85rem;
  text-align: center;
`;

const MoodBox = styled.div`
  margin-top: 16px;
  padding: 10px;
  background: rgba(102, 126, 234, 0.2);
  border-radius: 12px;
  text-align: center;
  color: white;
`;

const MoodEmoji = styled.span`
  font-size: 1.2rem;
`;

const MoodText = styled.span`
  margin-left: 8px;
  text-transform: capitalize;
  font-family: 'Nunito, sans-serif';
  font-weight: 700;
`;

const ActionSection = styled.div`
  margin-top: 16px;
  padding-top: 10px;
  border-top: 1px solid rgba(255, 255, 255, 0.2);
`;

const ActionColumn = styled.div`
  margin-top: 16px;
  padding-top: 10px;
  border-top: 1px solid rgba(255, 255, 255, 0.2);
  display: flex;
  flex-direction: column;
  gap: 8px;
`;

const ActionText = styled.div`
  color: white;
  font-family: 'Nunito, sans-serif';
  font-size: 0.9rem;
  text-align: center;
`;

const LogoutButton = styled.button`
  width: 100%;
  padding: 8px 12px;
  border-radius: 10px;
  border: none;
  background: rgba(0, 0, 0, 0.8);
  color: white;
  cursor: pointer;
  font-size: 0.9rem;
  transition: background 0.2s;
  font-family: 'Nunito, sans-serif';
  font-weight: 700;

  &:hover {
    background: rgba(244, 67, 54, 1);
  }
`;

const ReturnButton = styled.button`
  width: 100%;
  padding: 8px 12px;
  border-radius: 10px;
  border: none;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  color: white;
  cursor: pointer;
  font-size: 0.9rem;
  transition: background 0.2s;
  font-family: 'Nunito, sans-serif';
  font-weight: 700;
`;

type ViewingUser = {
  username?: string;
  avatarUrl?: string;
} | null;

interface PetStatsPanelProps {
  activePet: PetState;
  mood?: PetMood;
  isOwnPet: boolean;
  isStatsOpen: boolean;
  onToggleStats: () => void;
  viewingPetLoading: boolean;
  viewingPetError: string | null;
  viewingUser: ViewingUser;
  onLogout: () => void;
  onReturnToMyPet: () => void;
}

function getMoodEmoji(mood?: PetMood): string {
  if (mood === 'idle') return '🐱';
  if (mood === 'shy') return '😻';
  if (mood === 'happy') return '😺';
  if (mood === 'eating') return '😽';
  if (mood === 'laughing') return '😸';
  if (mood === 'sleepy') return '😴';
  if (mood === 'sad') return '😿';
  if (mood === 'dirty') return '🫧';
  if (mood === 'hungry') return '🍽️';
  if (mood === 'asleep') return '💤';
  if (mood === 'no') return '😾';
  if (mood === 'dead') return '👻';
  return '';
}

function getGaugeColor(value: number): string {
  if (value > 50) return '#4CAF50';
  if (value > 25) return '#FFC107';
  return '#F44336';
}

function StatRow({ label, value }: { label: string; value: number }) {
  const color = getGaugeColor(value);

  return (
    <StatItem>
      <StatLabel> {label}</StatLabel>
      <StatRowLine>
        <GaugeTrack>
          <GaugeFill $color={color} $value={value} />
        </GaugeTrack>
        <StatValue $color={color}>
          {value}%
        </StatValue>
      </StatRowLine>
    </StatItem>
  );
}

export default function PetStatsPanel({
  activePet,
  mood,
  isOwnPet,
  isStatsOpen,
  onToggleStats,
  viewingPetLoading,
  viewingPetError,
  viewingUser,
  onLogout,
  onReturnToMyPet,
}: PetStatsPanelProps) {
  return (
    <>
      {!isOwnPet && (
        <ReadOnlyBannerWrap>
          <ReadOnlyBanner>
            Read-only mode: you are visiting another user's Nekotchi.
          </ReadOnlyBanner>
        </ReadOnlyBannerWrap>
      )}

      <PanelAnchor>
      <ToggleButton
        isOpen={isStatsOpen}
        onClick={onToggleStats}
        label="Pet State"
        title={isStatsOpen ? 'Close stats' : 'Open stats'}
      />

      <StatsCard $isOpen={isStatsOpen}>
        <Title>
          ✦ {activePet.name} ✦
        </Title>

        {!isOwnPet && viewingPetLoading && (
          <StatusMessage>
            Loading stats...
          </StatusMessage>
        )}

        {!isOwnPet && viewingPetError && (
          <ErrorMessage>
            {viewingPetError}
          </ErrorMessage>
        )}

        <StatRow label="Hunger" value={activePet.hunger} />
        <StatRow label="Happy" value={activePet.happiness} />
        <StatRow label="Clean" value={activePet.cleanliness} />
        <StatRow label="Energy" value={activePet.energy} />

        <MoodBox>
          <MoodEmoji>{getMoodEmoji(mood)}</MoodEmoji>
          <MoodText>
            {mood}
          </MoodText>
        </MoodBox>

        {isOwnPet ? (
          <ActionSection>
            <LogoutButton
              onClick={onLogout}
            >
              ⏻ Logout
            </LogoutButton>
          </ActionSection>
        ) : (
          <ActionColumn>
            <ActionText>
              {viewingUser?.username ?? 'friend'}'s Nekotchi
            </ActionText>
            <ReturnButton
              onClick={onReturnToMyPet}
            >
              ← Return to my Nekotchi
            </ReturnButton>
          </ActionColumn>
        )}
      </StatsCard>
      </PanelAnchor>
    </>
  );
}
