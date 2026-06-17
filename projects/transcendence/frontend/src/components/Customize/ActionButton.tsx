import React from 'react';
import styled from 'styled-components';

type Props = {
  onClick?: (e?: any) => void;
  disabled?: boolean;
  small?: boolean;
  style?: React.CSSProperties;
  children: React.ReactNode;
};

const StyledButton = styled.button<{ $small?: boolean }>`
  margin-top: 4px;
  pointer-events: auto;
  padding: ${({ $small }) => ($small ? '8px 15px' : '8px 30px')};
  font-size: ${({ $small }) => ($small ? '0.95rem' : '0.8rem')};
  font-weight: bold;
  color: white;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  border: none;
  border-radius: 15px;
  cursor: pointer;
  transition: all 0.3s ease;
  box-shadow: 0 4px 15px rgba(102, 126, 234, 0.4);

  &:hover {
    transform: scale(1.05);
    box-shadow: 0 6px 25px rgba(102, 126, 234, 0.6);
  }

  &:disabled {
    cursor: not-allowed;
    opacity: 0.65;
    transform: none;
    box-shadow: 0 4px 15px rgba(102, 126, 234, 0.25);
  }
`;

export default function ActionButton({ onClick, disabled, small, style, children }: Props) {
  return (
    <StyledButton
      onClick={onClick}
      disabled={disabled}
      $small={small}
      style={style}
    >
      {children}
    </StyledButton>
  );
}
