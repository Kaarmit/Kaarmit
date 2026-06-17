import { useState, useEffect } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import { usePet } from '../../context/PetContext';
import { api } from '../../services/api';
import { motion, AnimatePresence } from 'framer-motion';
import styled from 'styled-components';
import type { CatType, UserCustomization } from '../../types';
import CatSelector from './CatSelector';
import ColorSelector from './ColorSelector';
import BackgroundSelector from './BackgroundSelector';
import ActionButton from './ActionButton';
import { DEFAULT_CAT_TYPE, DEFAULT_PET_BACKGROUND, DEFAULT_PET_COLOR } from '../../context/PetContext';

type Step = 'cat' | 'color' | 'name' | 'background';

const STEPS: Step[] = ['cat', 'color', 'name', 'background'];
const LABELS: Record<Step, string> = {
  cat: 'Choose your cat',
  name: 'Give a name to your cat',
  color: 'Select the color of your Nekotchi',
  background: 'Which background ?',
};

const PET_NAME_MIN_LENGTH = 3;
const PET_NAME_MAX_LENGTH = 20;
const AUTH_USER_KEY = 'auth_user';
const DRAFT_KEY = 'nekotchi-custom';

const FlowShell = styled.div`
  position: relative;
  min-height: 520px;
  overflow: visible;
`;

const FlowCard = styled.div`
  margin: 12px auto 0;
  background: rgba(10, 10, 30, 0.95);
  padding: 16px;
  border-radius: 12px;
  border: 2px solid rgba(255, 255, 255, 0.06);
  width: min(92vw, 760px);
  overflow: visible;
  z-index: 1;
`;

const StepCounter = styled.div`
  color: rgba(255, 255, 255, 0.6);
  font-size: 10px;
  margin-bottom: 8px;
  font-family: 'Press Start 2P';
  text-align: center;
`;

const StepTitle = styled.h3`
  color: white;
  margin-bottom: 20px;
  text-align: center;
  font-family: 'Nunito';
`;

const StageRow = styled.div`
  display: flex;
  gap: 12px;
  align-items: flex-start;
`;

const StageContent = styled.div`
  flex: 1;
`;

const ActionRow = styled.div`
  margin-top: 15px;
  display: flex;
  gap: 8px;
`;

const Spacer = styled.div`
  flex: 1;
`;

const NameStep = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
`;

const NameLabel = styled.label`
  color: white;
  font-family: 'Press Start 2P';
  text-align: center;
`;

const NameInput = styled.input`
  width: min(92%, 320px);
  margin-top: 8px;
  padding: 8px 10px;
  border-radius: 8px;
`;

const SplitActions = styled.div`
  display: flex;
  gap: 8px;
  margin-top: 15px;
  justify-content: space-between;
  width: 100%;
`;

const ActionGroup = styled.div`
  display: flex;
  gap: 8px;
`;

const BackgroundGroup = styled.div`
  margin-top: 15px;
  display: flex;
  gap: 8px;
  flex-direction: row;
`;

const FinishGroup = styled.div`
  flex: 1;
  display: flex;
  flex-direction: column;
`;

const ErrorMessage = styled.div`
  color: salmon;
  margin-bottom: 8px;
`;

const getCurrentUserId = (): number | null => {
  try {
    const rawUser = localStorage.getItem(AUTH_USER_KEY);
    if (!rawUser) {
      return null;
    }

    const parsedUser = JSON.parse(rawUser) as { id?: number };
    return typeof parsedUser.id === 'number' ? parsedUser.id : null;
  } catch {
    return null;
  }
};

const getDraftKey = (userId: number | null): string => (userId === null ? DRAFT_KEY : `${DRAFT_KEY}:${userId}`);

const syncStoredAuthUserCustomizations = (name: string, cat: string, color: string, background: string | null) => {
  try {
    const rawUser = localStorage.getItem(AUTH_USER_KEY);
    if (!rawUser) {
      return;
    }

    const parsedUser = JSON.parse(rawUser) as {
      catName?: string;
      customizations?: Partial<UserCustomization>;
      [key: string]: unknown;
    };

    const nextUser = {
      ...parsedUser,
      catName: name,
      customizations: {
        ...(parsedUser.customizations ?? {}),
        cat,
        color,
        background: background ?? DEFAULT_PET_BACKGROUND,
      },
    };

    localStorage.setItem(AUTH_USER_KEY, JSON.stringify(nextUser));
    window.dispatchEvent(new Event('auth-storage-changed'));
  } catch {
    // ignore localStorage sync failures
  }
};

// if resetCustomization is true, ignore any stored draft and return defaults customization parameters
const getInitialDraft = (resetCustomization: boolean) => {
  if (resetCustomization) {
    return {
      name: '',
      selectedCat: DEFAULT_CAT_TYPE as string | null,
      selectedColor: DEFAULT_PET_COLOR,
      selectedBackground: DEFAULT_PET_BACKGROUND,
    };
  }

  const raw = localStorage.getItem(getDraftKey(getCurrentUserId()));
  if (!raw) {
    return {
      name: '',
      selectedCat: null as string | null,
      selectedColor: null as string | null,
      selectedBackground: null as string | null,
    };
  }

  try {
    const data: Partial<UserCustomization> & { name?: string; cat?: string } = JSON.parse(raw);
    return {
      name: data.name ?? '',
      selectedCat: data.cat ?? null,
      selectedColor: data.color ?? null,
      selectedBackground: data.background ?? null,
    };
  } catch {
    return {
      name: '',
      selectedCat: null as string | null,
      selectedColor: null as string | null,
      selectedBackground: null as string | null,
    };
  }
};

export default function CustomizationFlow(): JSX.Element {
  const location = useLocation();
  const resetCustomization = Boolean((location.state as { resetCustomization?: boolean } | null)?.resetCustomization);
  const initialDraft = getInitialDraft(resetCustomization);

  const [name, setName] = useState<string>(initialDraft.name);
  const [stepIndex, setStepIndex] = useState<number>(0);
  const [direction, setDirection] = useState<number>(1);
  const [slideDistance, setSlideDistance] = useState<number>(300);
  const [selectedCat, setSelectedCat] = useState<string | null>(initialDraft.selectedCat);
  const [selectedColor, setSelectedColor] = useState<string | null>(initialDraft.selectedColor);
  const [selectedBackground, setSelectedBackground] = useState<string | null>(initialDraft.selectedBackground);

  const navigate = useNavigate();
  const { setColor, setSelectedBackground: setCtxBackground, setCatType, setPetName } = usePet();

  const [isSaving, setIsSaving] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const trimmedName = name.trim();

  const goTo = (index: number, dir = 1) => {
    setDirection(dir);
    setStepIndex(Math.max(0, Math.min(index, STEPS.length - 1)));
  };

  const nextStep = () => {
    if (stepIndex <= STEPS.length - 1) {
      setSlideDistance(600);
      goTo(stepIndex + 1, +1);
    }
  };

  const prevStep = () => {
    if (stepIndex >= 0) {
      setSlideDistance(600);
      goTo(stepIndex - 1, -1);
    }
  };

  useEffect(() => {
    if (resetCustomization) {
      localStorage.removeItem(getDraftKey(getCurrentUserId()));
    }

    const prefs: Partial<UserCustomization> & { name?: string; cat?: string } = {
      name,
      cat: selectedCat ?? undefined,
      color: selectedColor ?? undefined,
      background: selectedBackground ?? undefined,
    };
    localStorage.setItem(getDraftKey(getCurrentUserId()), JSON.stringify(prefs));
  }, [name, selectedCat, selectedColor, selectedBackground, resetCustomization]);

  // Sync selections to global PetContext for live preview
  useEffect(() => {
    if (selectedCat) {
      try { setCatType(selectedCat as CatType); } catch { }
    }
  }, [selectedCat, setCatType]);

  useEffect(() => {
    if (selectedColor) {
      try { setColor(selectedColor); } catch { }
    }
  }, [selectedColor, setColor]);

  useEffect(() => {
    if (selectedBackground) {
      try { setCtxBackground(selectedBackground); } catch { }
    }
  }, [selectedBackground, setCtxBackground]);

  const onFinish = async () => {
    if (!trimmedName || !selectedCat || !selectedColor) {
      setError('Please fill in all fields.');
      return;
    }

    if (trimmedName.length < PET_NAME_MIN_LENGTH || trimmedName.length > PET_NAME_MAX_LENGTH) {
      setError(`The name of the pet must contain between ${PET_NAME_MIN_LENGTH} and ${PET_NAME_MAX_LENGTH} characters.`);
      return;
    }

    setIsSaving(true);
    setError(null);

    const payload: Partial<UserCustomization> & { name: string; cat: string } = {
      name: trimmedName,
      cat: selectedCat!,
      color: selectedColor!,
      background: selectedBackground ?? undefined,
    };

    try {
      await api.post('/pets', payload);
      setPetName(trimmedName);
      setColor(selectedColor!);
      setCtxBackground(selectedBackground ?? '');
      setCatType(selectedCat as any);
      syncStoredAuthUserCustomizations(trimmedName, selectedCat!, selectedColor!, selectedBackground);
      // App routes mount the personal Nekotchi page at `/nekotchi/me` (protected route).
      // Redirect there after saving (no per-id route currently).
      navigate('/nekotchi/me', { replace: true });
    } catch {
      // dev fallback
      if (import.meta?.env?.DEV) {
        setPetName(trimmedName);
        setColor(selectedColor!);
        setCtxBackground(selectedBackground ?? '');
        setCatType(selectedCat as any);
        syncStoredAuthUserCustomizations(trimmedName, selectedCat!, selectedColor!, selectedBackground);
        navigate('/nekotchi/me', { replace: true });
        return;
      }
      setError('Unable to save. Please try again.');
    } finally {
      setIsSaving(false);
    }
  };

  return (
    <FlowShell>
      <FlowCard>
        <StepCounter>Step: {stepIndex + 1}/{STEPS.length}</StepCounter>

        <AnimatePresence initial={false} mode="wait" custom={direction}>
          <motion.div
            key={STEPS[stepIndex]}
            custom={direction}
            initial={{ x: direction > 0 ? slideDistance : -slideDistance, opacity: 0 }}
            animate={{ x: 0, opacity: 1 }}
            exit={{ x: direction > 0 ? -slideDistance : slideDistance, opacity: 0 }}
            transition={{ type: 'spring', stiffness: 300, damping: 30 }}
            style={{ width: '100%' }}
          >
            <StepTitle>{LABELS[STEPS[stepIndex]]}</StepTitle>

            <StageRow>
              <StageContent>

                {STEPS[stepIndex] === 'cat' && (
                  <div>
                    <CatSelector selected={selectedCat} onSelect={(c: string) => { setSelectedCat(c); }} />
                    <ActionRow>
                      <Spacer />
                      <ActionButton onClick={nextStep} disabled={!selectedCat}>Next</ActionButton>
                    </ActionRow>
                  </div>
                )}

                {STEPS[stepIndex] === 'name' && (
                  <NameStep>
                    <NameLabel>Name</NameLabel>
                    <NameInput
                      aria-label="pet-name"
                      value={name}
                      maxLength={PET_NAME_MAX_LENGTH}
                      onChange={e => {
                        setName(e.target.value);
                        if (error) {
                          setError(null);
                        }
                      }}
                    />
                    <SplitActions>
                      <ActionGroup>
                        <ActionButton onClick={prevStep} disabled={stepIndex === 0}>Back</ActionButton>
                      </ActionGroup>
                      <ActionGroup>
                        <ActionButton onClick={nextStep} disabled={!trimmedName}>Next</ActionButton>
                      </ActionGroup>
                    </SplitActions>
                  </NameStep>
                )}

                {STEPS[stepIndex] === 'color' && (
                  <div>
                    <ColorSelector selected={selectedColor} onSelect={(c: string) => { setSelectedColor(c); }} />
                    <ActionRow>
                      <ActionButton onClick={prevStep} disabled={stepIndex === 0}>Back</ActionButton>
                      <Spacer />
                      <ActionButton onClick={nextStep} disabled={!selectedColor}>Next</ActionButton>
                    </ActionRow>
                  </div>
                )}

                {STEPS[stepIndex] === 'background' && (
                  <div>
                    <BackgroundSelector selected={selectedBackground} onSelect={(c: string) => { setSelectedBackground(c); }} />
                    <BackgroundGroup>
                      <ActionButton onClick={prevStep} disabled={stepIndex === 0}>Back</ActionButton>
                      <FinishGroup>
                        {error && <ErrorMessage>{error}</ErrorMessage>}
                        <ActionButton onClick={onFinish} disabled={isSaving} small>
                          {isSaving ? 'Saving...' : 'Save'}
                        </ActionButton>
                      </FinishGroup>
                    </BackgroundGroup>
                  </div>
                )}
              </StageContent>
            </StageRow>
          </motion.div>
        </AnimatePresence>
      </FlowCard>
    </FlowShell>
  );
}

