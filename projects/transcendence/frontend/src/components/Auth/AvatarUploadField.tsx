import type { ChangeEvent } from 'react';
import styled from 'styled-components';

interface AvatarUploadFieldProps {
  loading: boolean;
  avatarPreviewUrl: string | null;
  onAvatarChange: (event: ChangeEvent<HTMLInputElement>) => void;
}

const UploadContainer = styled.div`
  display: grid;
  gap: 10px;
`;

const UploadLabel = styled.label`
  color: #fff;
  font-size: 0.9rem;
`;

const UploadContent = styled.div`
  display: grid;
  gap: 6px;
`;

const UploadInput = styled.input`
  width: 200px;
  margin: 0 auto;
  padding: 8px 10px;
  border-radius: 10px;
  border: 1px solid rgba(255, 255, 255, 0.35);
  color: #fff;
  background: rgba(255, 255, 255, 0.05);

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const PreviewWrapper = styled.div<{ $size: number }>`
  width: ${({ $size }) => $size}px;
  height: ${({ $size }) => $size}px;
  margin: 0 auto;
  display: grid;
  place-items: center;
`;

const PreviewImage = styled.img`
  width: 100%;
  height: 100%;
  border-radius: 50%;
  object-fit: cover;
  border: 1px solid rgba(255, 255, 255, 0.35);
`;

export default function AvatarUploadField({
  loading,
  avatarPreviewUrl,
  onAvatarChange,
}: AvatarUploadFieldProps) {
  const previewSize = 74;

  return (
    <UploadContainer>
      <UploadLabel htmlFor="avatar-upload">Avatar (optional)</UploadLabel>
      <UploadContent>
        <UploadInput
          id="avatar-upload"
          type="file"
          accept="image/*"
          onChange={onAvatarChange}
          disabled={loading}
        />
        <PreviewWrapper $size={previewSize}>
          {avatarPreviewUrl && (
            <PreviewImage src={avatarPreviewUrl} alt="Aperçu avatar" />
          )}
        </PreviewWrapper>
      </UploadContent>
    </UploadContainer>
  );
}