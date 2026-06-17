import { useCallback, useEffect, useState, type FormEvent } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import styled from 'styled-components';
import FormEnvironment from '../FormEnvironment';
import AvatarUploadField from './AvatarUploadField';
import useAvatarUpload from '../../hooks/useAvatarUpload';
import { useAuth } from '../../hooks/useAuth';
import { api } from '../../services/api';
import type { UpdateProfilePayload } from '../../types';

const MainContainer = styled.main`
  height: 100vh;
  min-height: 100vh;
  width: 100%;
  display: grid;
  place-items: center;
  position: relative;
  overflow-x: hidden;
  overflow-y: auto;
  padding: 1rem 1rem 5.5rem;
`;

const BackgroundOverlay = styled.div`
  position: absolute;
  inset: 0;
  z-index: 0;
`;

const StyledForm = styled.form<{ $showForm: boolean }>`
  display: grid;
  align-content: center;
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
  opacity: ${({ $showForm }) => ($showForm ? 1 : 0)};
  transition: opacity 0.5s ease-in-out;
`;

const FormContent = styled.div`
  width: 100%;
  max-width: 180px;
  margin: 0 auto;
  display: grid;
  gap: 8px;
  transform: translateX(-8px);
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
  padding: 8px 10px;
  border-radius: 10px;
  border: 1px solid rgba(255, 255, 255, 0.35);
  background: rgba(255, 255, 255, 0.05);
  color: #fff;

  &::placeholder {
    color: rgba(255, 255, 255, 0.5);
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const StyledButton = styled.button<{ $danger?: boolean }>`
  width: 180px;
  margin: 0 auto;
  padding: 8px 10px;
  border-radius: 10px;
  border: 0;
  color: #fff;
  background: ${({ $danger }) => ($danger ? '#ff6b6b' : 'rgba(102, 126, 234, 0.7)')};
  cursor: pointer;
  font-family: 'Nunito', sans-serif;
  font-weight: 600;
  transition: background 0.2s ease, opacity 0.2s ease;

  &:hover:not(:disabled) {
    background: ${({ $danger }) => ($danger ? '#ff5a5a' : 'rgba(102, 126, 234, 0.9)')};
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const ErrorMessage = styled.p`
  color: #ff6b6b;
  margin: 0;
`;

const SuccessMessage = styled.p`
  color: #a8ffb0;
  margin: 0;
`;

const LegalLinksContainer = styled.footer`
  position: absolute;
  bottom: 8px;
  left: 0;
  right: 0;
  width: 100%;
  padding: 12px;
  display: flex;
  justify-content: center;
  gap: 16px;
  flex-wrap: wrap;
  z-index: 1;

  a {
    color: #66ccff;
    text-decoration: none;
    font-size: 0.875rem;

    &:hover {
      color: #ff99cc;
    }
  }
`;

const TwoFactorBox = styled.div`
  width: 180px;
  margin: 8px auto 0;
  display: grid;
  gap: 8px;
  justify-items: center;
`;

const QrCodeImage = styled.img`
  width: 150px;
  height: 150px;
  border-radius: 8px;
  background: #fff;
  padding: 6px;
`;

const SmallText = styled.p`
  color: rgba(255, 255, 255, 0.75);
  font-size: 0.75rem;
  margin: 0;
  text-align: center;
`;

type TwoFactorSetupResponse = {
  qrCodeUrl: string;
};

export default function UpdateProfile() {
  const navigate = useNavigate();
  const { user, loading: authLoading, error: authError, clearError, refreshUser } = useAuth();

  const [username, setUsername] = useState(user?.username ?? '');
  const [password, setPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [twoFactorCode, setTwoFactorCode] = useState('');
  const [qrCodeUrl, setQrCodeUrl] = useState('');
  const [twoFactorLoading, setTwoFactorLoading] = useState(false);
  const [error, setError] = useState('');
  const [success, setSuccess] = useState('');
  const [showForm, setShowForm] = useState(false);
  const [loading, setLoading] = useState(false);

  const clearMessages = useCallback(() => {
    setError('');
    setSuccess('');
    clearError();
  }, [clearError]);

  useEffect(() => {
    const timer = setTimeout(() => setShowForm(true), 600);
    return () => clearTimeout(timer);
  }, []);

  const { avatarPreviewUrl, avatarAsDataUrl, handleAvatarChange } = useAvatarUpload({
    onValidationError: setError,
    onValidSelection: clearMessages,
  });

  const handleSubmit = async (event: FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    clearMessages();

    if (!username.trim()) {
      setError('Username required');
      return;
    }

    if (password && password !== confirmPassword) {
      setError('Passwords do not match');
      return;
    }

    if (!password && !username && !avatarPreviewUrl) {
      setError('No changes to save');
      return;
    }

    setLoading(true);
    try {
      const payload: UpdateProfilePayload = {};
      
      if (username !== user?.username) {
        payload.newUsername = username;
      }
      
      if (password) {
        payload.newPassword = password;
      }
      
      if (avatarPreviewUrl && avatarPreviewUrl !== user?.avatarUrl) {
        payload.newAvatarUrl = avatarAsDataUrl || undefined;
      }

      if (Object.keys(payload).length === 0) {
        setError('No changes to save');
        return;
      }

      await api.put('/users/profile', payload);
      setSuccess('Profile updated successfully');
      setPassword('');
      setConfirmPassword('');
      
      await refreshUser?.();
      
      setTimeout(() => {
        navigate('/nekotchi/me');
      }, 1500);
    } catch (err: any) {
      setError(err.response?.data?.error || 'Failed to update profile');
    } finally {
      setLoading(false);
    }
  };

  const handleSetupTwoFactor = async () => {
    clearMessages();

    if (!user?.id) {
      setError('You must be logged in to enable 2FA.');
      return;
    }

    try {
      setTwoFactorLoading(true);

      const response = await api.post<TwoFactorSetupResponse>('/auth/2fa/setup', {
        userId: user.id,
      });

      setQrCodeUrl(response.data.qrCodeUrl);
      setSuccess('Scan the QR code with your authenticator app.');
    } catch {
      setError('Failed to generate 2FA QR code.');
    } finally {
      setTwoFactorLoading(false);
    }
  };

  const handleConfirmTwoFactor = async () => {
    clearMessages();

    if (!user?.id) {
      setError('You must be logged in to confirm 2FA.');
      return;
    }

    if (!twoFactorCode.trim()) {
      setError('Enter the 6-digit code from your authenticator app.');
      return;
    }

    try {
      setTwoFactorLoading(true);

      await api.post('/auth/2fa/confirm', {
        userId: user.id,
        code: twoFactorCode.trim(),
      });

      setQrCodeUrl('');
      setTwoFactorCode('');
      setSuccess('2FA enabled successfully.');
    } catch {
      setError('Invalid 2FA code.');
    } finally {
      setTwoFactorLoading(false);
    }
  };

  return (
    <MainContainer>
      <BackgroundOverlay>
        <FormEnvironment cameraPosition={[0, 0, 18]} />
      </BackgroundOverlay>

      <StyledForm onSubmit={handleSubmit} $showForm={showForm}>
        <FormContent>
          <StyledTitle>Edit Profile</StyledTitle>

          <AvatarUploadField
            loading={authLoading || loading}
            avatarPreviewUrl={avatarPreviewUrl ?? user?.avatarUrl ?? null}
            onAvatarChange={handleAvatarChange}
          />

          <StyledInput
            type="text"
            placeholder="Username"
            value={username}
            onChange={(event) => {
              setUsername(event.target.value);
              if (error || authError || success) {
                clearMessages();
              }
            }}
            disabled={authLoading || loading}
          />

          <StyledInput
            type="password"
            placeholder="New Password"
            value={password}
            onChange={(event) => {
              setPassword(event.target.value);
              if (error || authError || success) {
                clearMessages();
              }
            }}
            disabled={authLoading || loading}
          />

          <StyledInput
            type="password"
            placeholder="Confirm New Password"
            value={confirmPassword}
            onChange={(event) => {
              setConfirmPassword(event.target.value);
              if (error || authError || success) {
                clearMessages();
              }
            }}
            disabled={authLoading || loading}
          />

          <StyledButton type="button" onClick={handleSetupTwoFactor} disabled={authLoading || twoFactorLoading || loading}>
            {twoFactorLoading ? 'Loading...' : 'Enable 2FA'}
          </StyledButton>

          {qrCodeUrl && (
            <TwoFactorBox>
              <SmallText>Scan this QR code, then enter the 6-digit code.</SmallText>

              <QrCodeImage src={qrCodeUrl} alt="2FA QR code" />

              <StyledInput
                type="text"
                placeholder="6-digit code"
                value={twoFactorCode}
                onChange={(event) => setTwoFactorCode(event.target.value)}
                maxLength={6}
                disabled={authLoading || twoFactorLoading || loading}
              />

              <StyledButton type="button" onClick={handleConfirmTwoFactor} disabled={authLoading || twoFactorLoading}>
                Confirm 2FA
              </StyledButton>
            </TwoFactorBox>
          )}

          {(error || authError) && <ErrorMessage>{error || authError}</ErrorMessage>}
          {success && <SuccessMessage>{success}</SuccessMessage>}

          <StyledButton type="submit" disabled={authLoading || loading}>
            {loading ? 'Saving...' : 'Submit'}
          </StyledButton>

          <StyledButton type="button" onClick={() => navigate('/nekotchi/me')} disabled={authLoading || loading}>
            Back
          </StyledButton>
        </FormContent>
      </StyledForm>

        <LegalLinksContainer>
          <Link to="/privacy">Privacy Policy</Link>
          <Link to="/terms">Terms of Service</Link>
        </LegalLinksContainer>

    </MainContainer>
  );
}