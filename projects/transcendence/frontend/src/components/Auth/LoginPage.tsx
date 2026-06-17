import { useNavigate, useLocation, Link } from 'react-router-dom';
import { useState, useEffect, type FormEvent } from 'react';
import styled from 'styled-components';
import axios from 'axios';
import FormEnvironment from '../FormEnvironment';
import { useAuth } from '../../hooks/useAuth';
import { api } from '../../services/api';
import type { AuthUser } from '../../types';

const TOKEN_KEY = 'auth_token';
const USER_KEY = 'auth_user';

type LoginResponse = {
  user?: AuthUser;
  token?: string;
  requires2FA?: boolean;
  tempToken?: string;
};

const storeAuth = (token: string, user: AuthUser) => {
  localStorage.setItem(TOKEN_KEY, token);
  localStorage.setItem(USER_KEY, JSON.stringify(user));
  window.dispatchEvent(new Event('auth-storage-changed'));
};

const getApiError = (error: unknown, fallback: string) => {
  if (axios.isAxiosError(error)) {
    const data = error.response?.data as { error?: string; message?: string } | undefined;
    return data?.error ?? data?.message ?? fallback;
  }
  return fallback;
};

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
  max-width: 180px;
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
  width: 180px;
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
  width: 180px;
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

export default function LoginPage() {
  const navigate = useNavigate();
  const location = useLocation();
  const { isAuthenticated, loading: authLoading, error: authError } = useAuth();

  const [identifier, setIdentifier] = useState('');
  const [password, setPassword] = useState('');
  const [twoFactorCode, setTwoFactorCode] = useState('');
  const [tempToken, setTempToken] = useState('');
  const [requires2FA, setRequires2FA] = useState(false);
  const [localLoading, setLocalLoading] = useState(false);
  const [error, setError] = useState('');
  const [showForm, setShowForm] = useState(false);

  const from = (location.state as { from?: { pathname: string } })?.from?.pathname || null;

  useEffect(() => {
    if (isAuthenticated && from) navigate(from, { replace: true });
  }, [isAuthenticated, navigate, from]);

  useEffect(() => {
    const timer = setTimeout(() => setShowForm(true), 600);
    return () => clearTimeout(timer);
  }, []);

  const handleSubmit = async (event: FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    setError('');

    if (!identifier.trim() || !password.trim()) {
      setError('Email/username and password are required.');
      return;
    }

    const trimmedIdentifier = identifier.trim();
    const isEmail = trimmedIdentifier.includes('@');
    const loginRequestBody = isEmail
      ? { email: trimmedIdentifier, password }
      : { username: trimmedIdentifier, password };

    try {
      setLocalLoading(true);

      const response = await api.post<LoginResponse>('/auth/login', loginRequestBody);

      if (response.data.requires2FA && response.data.tempToken) {
        setTempToken(response.data.tempToken);
        setRequires2FA(true);
        setLocalLoading(false);
        return;
      }

      if (!response.data.token || !response.data.user) {
        throw new Error('Invalid login response');
      }

      storeAuth(response.data.token, response.data.user);
      navigate(from || '/nekotchi/me', { replace: true });
    } catch (err: unknown) {
      setError(getApiError(err, 'Login failed.'));
      setLocalLoading(false);
    }
  };

  const handleTwoFactorSubmit = async (event: FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    setError('');

    if (!twoFactorCode.trim()) {
      setError('2FA code is required.');
      return;
    }

    try {
      setLocalLoading(true);

      const response = await api.post<LoginResponse>('/auth/2fa/verify-login', {
        tempToken,
        code: twoFactorCode.trim(),
      });

      if (!response.data.token || !response.data.user) {
        throw new Error('Invalid 2FA response');
      }

      storeAuth(response.data.token, response.data.user);
      navigate(from || '/nekotchi/me', { replace: true });
    } catch (err: unknown) {
      setError(getApiError(err, 'Invalid 2FA code.'));
      setLocalLoading(false);
    }
  };

  const loading = authLoading || localLoading;

  return (
    <MainContainer>
      <BackgroundOverlay>
        <FormEnvironment cameraPosition={[0, 0, 18]} />
      </BackgroundOverlay>

      <StyledForm onSubmit={requires2FA ? handleTwoFactorSubmit : handleSubmit} $showForm={showForm}>
        <InputContainer>
          <StyledTitle>{requires2FA ? '2FA Code' : 'Login'}</StyledTitle>

          {!requires2FA && (
            <>
              <StyledInput
                type="text"
                placeholder="Email or Username"
                value={identifier}
                onChange={event => setIdentifier(event.target.value)}
                disabled={loading}
              />
              <StyledInput
                type="password"
                placeholder="Password"
                value={password}
                onChange={event => setPassword(event.target.value)}
                disabled={loading}
              />
            </>
          )}

          {requires2FA && (
            <StyledInput
              type="text"
              placeholder="6-digit code"
              value={twoFactorCode}
              onChange={event => setTwoFactorCode(event.target.value)}
              disabled={loading}
              maxLength={6}
            />
          )}

          {(error || authError) && <ErrorMessage>{error || authError}</ErrorMessage>}

          <StyledButton type="submit" disabled={loading}>
            {loading ? 'Signing in...' : requires2FA ? 'Verify code' : 'Log in'}
          </StyledButton>

          {!requires2FA && (
            <StyledButton type="button" onClick={() => navigate('/register')} disabled={loading}>
              I don't have an account
            </StyledButton>
          )}

          {requires2FA && (
            <StyledButton type="button" onClick={() => setRequires2FA(false)} disabled={loading}>
              Back to login
            </StyledButton>
          )}
        </InputContainer>
      </StyledForm>
      <LegalLinksContainer>
        <Link to="/privacy">Privacy Policy</Link>
        <Link to="/terms">Terms of Service</Link>
      </LegalLinksContainer>
    </MainContainer>
  );
}