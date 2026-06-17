import type { ButtonHTMLAttributes, ReactNode } from 'react';
import styled from 'styled-components';

interface ToggleButtonProps extends ButtonHTMLAttributes<HTMLButtonElement> {
    isOpen: boolean;
    onClick: () => void;
    label: string;
    badge?: ReactNode;
    title?: string;
}

const StyledButton = styled.button`
    border: none;
    border-radius: clamp(10px, 2.5vw, 14px);
    padding: clamp(10px, 2vw, 14px);
    cursor: pointer;
    background: rgba(10, 10, 30, 0.9);
    color: white;
    border: 2px solid rgba(102, 126, 234, 0.5);
    backdrop-filter: blur(10px);
    font-family: 'Press Start 2P', cursive;
    font-size: clamp(0.46rem, 1.8vw, 0.62rem);
    display: inline-flex;
    align-items: center;
    justify-content: space-between;
    gap: clamp(6px, 1.8vw, 8px);
    box-shadow: 0 6px 20px rgba(0, 0, 0, 0.35);
    width: fit-content;
    min-width: 0;
    max-width: 100%;
    white-space: nowrap;
    pointer-events: auto;
`;

const Arrow = styled.span`
    color: #ffffff;
    font-family: 'Press Start 2P', cursive;
    font-size: 0.52rem;
`;

const Badge = styled.span`
    color: #bcd4ff;
    font-family: 'Nunito', sans-serif;
    font-size: 0.76rem;
    font-weight: 700;
`;

export default function ToggleButton({
    isOpen,
    onClick,
    label,
    badge,
    title,
}: ToggleButtonProps) {
    return (
        <StyledButton onClick={onClick} title={title}>
            {label}
            <Arrow>{isOpen ? '▲' : '▼'}</Arrow>
            {badge && <Badge>{badge}</Badge>}
        </StyledButton>
    );
}
