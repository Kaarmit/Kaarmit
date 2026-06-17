import { useCallback, useState, useEffect, type FormEvent } from 'react';
import { useNavigate, useLocation, Link } from 'react-router-dom';
import styled from 'styled-components';
import FormEnvironment from '../FormEnvironment';
import AvatarUploadField from './AvatarUploadField';
import { useAuth } from '../../hooks/useAuth';
import useAvatarUpload from '../../hooks/useAvatarUpload';
import { usePet, DEFAULT_PET_COLOR, DEFAULT_PET_BACKGROUND, DEFAULT_CAT_TYPE } from '../../context/PetContext';

const USERNAME_MIN_LENGTH = 3;
const USERNAME_MAX_LENGTH = 20;
const EMAIL_MAX_LENGTH = 100;
const PASSWORD_MIN_LENGTH = 8;
const PASSWORD_MAX_LENGTH = 30;

const MainContainer = styled.main`
  height: 100vh;
  min-height: 100vh;
  width: 100%;
  display: grid;
  place-items: center;
  position: relative;
  overflow-x: hidden;
  overflow-y: auto;
  padding: 1rem;
`;

const BackgroundOverlay = styled.div`
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 0;
`;

const StyledForm = styled.form<{ $showForm: boolean }>`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  position: relative;
  z-index: 1;
  background: linear-gradient(180deg, rgba(255, 255, 255, 0.06), rgba(255, 255, 255, 0.02));
  width: 100%;
  max-height: calc(100vh - 2rem);
  overflow-y: auto;
  -webkit-overflow-scrolling: touch;
  gap: 8px;
  max-width: 380px;
  min-height: 480px;
  padding: 32px 32px 40px;
  border-radius: 52% 52% 44% 44% / 68% 68% 36% 36%;
  box-shadow: 0 10px 30px rgba(0, 0, 0, 0.45), inset 0 1px 0 rgba(255, 255, 255, 0.03);
  opacity: ${props => (props.$showForm ? 1 : 0)};
  transition: opacity 0.5s ease-in-out;
`;

const InputContainer = styled.div`
  width: 100%;
  max-width: 200px;
  margin: 0 auto;
  display: grid;
  gap: 6px;
`;

const StyledTitle = styled.h1`
  color: #fff;
  margin: 0;
  text-align: center;
  font-family: 'Press Start 2P', cursive;
  font-size: 1.2rem;
`;

const StyledInput = styled.input`
  width: 200px;
  margin: 0 auto;
  padding: 4px 6px;
  border-radius: 6px;
  border: 1px solid rgba(255, 255, 255, 0.35);
  background: rgba(255, 255, 255, 0.05);
  color: white;

  &::placeholder {
    color: rgba(255, 255, 255, 0.5);
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const StyledButton = styled.button`
  width: 200px;
  margin: 0 auto;
  padding: 4px 6px;
  border-radius: 6px;
  border: none;
  background: rgba(102, 126, 234, 0.7);
  color: white;
  cursor: pointer;
  font-family: 'Nunito', sans-serif;
  font-weight: 600;
  transition: background 0.2s ease;

  &:hover:not(:disabled) {
    background: rgba(102, 126, 234, 0.9);
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const ErrorMessage = styled.p`
  color: #ff6b6b;
  margin: 0;
  font-size: 0.9rem;
  text-align: center;
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
  z-index: 1;

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

export default function RegisterPage() {
  const navigate = useNavigate();
  const location = useLocation();
  const { register, loading: authLoading, error: authError, clearError } = useAuth();
  const [username, setUsername] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');
  const [showForm, setShowForm] = useState(false);
  const pet = usePet();
  const clearAuthAndLocalErrors = useCallback(() => {
    setError('');
    clearError();
  }, [clearError]);
  const { avatar, avatarPreviewUrl, handleAvatarChange } = useAvatarUpload({
    onValidationError: setError,
    onValidSelection: clearAuthAndLocalErrors,
  });
  const redirectTo =
    (location.state as { from?: { pathname: string } })?.from?.pathname || '/customize';

  useEffect(() => {
    const timer = setTimeout(() => setShowForm(true), 600);
    return () => clearTimeout(timer);
  }, []);

  const handleSubmit = async (event: FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    setError('');
    clearError();

    const trimmedUsername = username.trim();
    const trimmedEmail = email.trim();

    if (!trimmedUsername || !trimmedEmail || !password.trim()) {
      setError('You must fill in all fields.');
      return;
    }

    if (trimmedUsername.length < USERNAME_MIN_LENGTH || trimmedUsername.length > USERNAME_MAX_LENGTH) {
      setError(`The username must contain between ${USERNAME_MIN_LENGTH} and ${USERNAME_MAX_LENGTH} characters.`);
      return;
    }

    if (trimmedEmail.length > EMAIL_MAX_LENGTH) {
      setError(`The email must not exceed ${EMAIL_MAX_LENGTH} characters.`);
      return;
    }

    if (password.length > PASSWORD_MAX_LENGTH) {
      setError(`The password must not exceed ${PASSWORD_MAX_LENGTH} characters.`);
      return;
    }

    if (password.length < PASSWORD_MIN_LENGTH) {
      setError(`The password must be at least ${PASSWORD_MIN_LENGTH} characters long.`);
      return;
    }

    const passwordRegex = /^(?=.*\d)(?=.*[@$!%*?&.])[A-Za-z\d@$!%*?&.]{8,}$/;
    if (!passwordRegex.test(password)) {
      setError(
        `Password must be at least ${PASSWORD_MIN_LENGTH} characters long and include a number and a special character.`
      );
      return;
    }

    const success = await register({
      avatar,
      username: trimmedUsername,
      email: trimmedEmail,
      password,
      cat: pet?.catType ?? DEFAULT_CAT_TYPE,
      color: pet?.color ?? DEFAULT_PET_COLOR,
      background: pet?.selectedBackground ?? DEFAULT_PET_BACKGROUND,
    });
    if (success) {
      navigate(redirectTo, { replace: true, state: { resetCustomization: true } });
    }
  };

  const loading = authLoading;

  return (
    <MainContainer>
      <BackgroundOverlay>
        <FormEnvironment />
      </BackgroundOverlay>

      <StyledForm onSubmit={handleSubmit} $showForm={showForm}>
        <InputContainer>
          <StyledTitle>Register</StyledTitle>

          <AvatarUploadField
            loading={loading}
            avatarPreviewUrl={avatarPreviewUrl}
            onAvatarChange={handleAvatarChange}
          />

          <StyledInput
            type="text"
            placeholder="Username"
            value={username}
            minLength={USERNAME_MIN_LENGTH}
            maxLength={USERNAME_MAX_LENGTH}
            onChange={(event) => {
              setUsername(event.target.value);
              if (error || authError) {
                setError('');
                clearError();
              }
            }}
            disabled={loading}
          />
          <StyledInput
            type="email"
            placeholder="Email"
            value={email}
            maxLength={EMAIL_MAX_LENGTH}
            onChange={(event) => {
              setEmail(event.target.value);
              if (error || authError) {
                setError('');
                clearError();
              }
            }}
            disabled={loading}
          />
          <StyledInput
            type="password"
            placeholder="Password"
            value={password}
            onChange={(event) => {
              setPassword(event.target.value);
              if (error || authError) {
                setError('');
                clearError();
              }
            }}
            disabled={loading}
          />

          {(error || authError) && <ErrorMessage>{error || authError}</ErrorMessage>}

          <StyledButton type="submit" disabled={loading}>
            {loading ? 'Creating account...' : 'Submit'}
          </StyledButton>

          <StyledButton type="button" onClick={() => navigate('/login')} disabled={loading}>
            I already have an account
          </StyledButton>
        </InputContainer>
      </StyledForm>
      <LegalLinksContainer>
        <Link to="/privacy">Privacy Policy</Link>
        <Link to="/terms">Terms of Service</Link>
      </LegalLinksContainer>
    </MainContainer>
  );
}