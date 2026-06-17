import { useCallback, useEffect, useState, type ChangeEvent } from 'react';

interface UseAvatarUploadOptions {
  maxAvatarSizeMb?: number;
  onValidationError?: (message: string) => void;
  onValidSelection?: () => void;
}

export default function useAvatarUpload({
  maxAvatarSizeMb = 3,
  onValidationError,
  onValidSelection,
}: UseAvatarUploadOptions = {}) {
  const [avatar, setAvatar] = useState<File | null>(null);
  const [avatarAsDataUrl, setAvatarAsDataUrl] = useState<string | null>(null);
  const [avatarPreviewUrl, setAvatarPreviewUrl] = useState<string | null>(null);

  useEffect(() => {
    return () => {
      if (avatarPreviewUrl) {
        URL.revokeObjectURL(avatarPreviewUrl);
      }
    };
  }, [avatarPreviewUrl]);

  const handleAvatarChange = useCallback(async (event: ChangeEvent<HTMLInputElement>) => {
    const selectedFile = event.target.files?.[0] ?? null;

    if (!selectedFile) {
      if (avatarPreviewUrl) {
        URL.revokeObjectURL(avatarPreviewUrl);
      }
      setAvatar(null);
      setAvatarAsDataUrl(null);
      setAvatarPreviewUrl(null);
      return;
    }

    if (!selectedFile.type.startsWith('image/')) {
      onValidationError?.('The file must be an image.');
      event.target.value = '';
      return;
    }

    if (selectedFile.size > maxAvatarSizeMb * 1024 * 1024) {
      onValidationError?.(`The avatar must be less than ${maxAvatarSizeMb}MB.`);
      event.target.value = '';
      return;
    }

    if (avatarPreviewUrl) {
      URL.revokeObjectURL(avatarPreviewUrl);
    }

    const nextPreviewUrl = URL.createObjectURL(selectedFile);
    setAvatar(selectedFile);
    setAvatarPreviewUrl(nextPreviewUrl);
    onValidSelection?.();

    try {
      const dataUrl = await new Promise<string>((resolve, reject) => {
        const reader = new FileReader();
        reader.onload = () => {
          if (typeof reader.result === 'string') {
            resolve(reader.result);
          } else {
            reject(new Error('Failed to read avatar file.'));
          }
        };
        reader.onerror = () => reject(new Error('Failed to read avatar file.'));
        reader.readAsDataURL(selectedFile);
      });
      setAvatarAsDataUrl(dataUrl);
    } catch (error) {
      onValidationError?.(error instanceof Error ? error.message : 'Could not process image.');
    }
  }, [avatarPreviewUrl, maxAvatarSizeMb, onValidationError, onValidSelection]);

  return {
    avatar,
    avatarAsDataUrl,
    avatarPreviewUrl,
    handleAvatarChange,
  };
}