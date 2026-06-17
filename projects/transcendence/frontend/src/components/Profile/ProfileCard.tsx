import { useState } from 'react';
import styled from 'styled-components';

interface Props {
    forceOpen?: boolean;
    avatarUrl?: string;
    username: string;
    email: string;
    inline?: boolean;
    showEditButton?: boolean;
    onEditClick?: () => void;
}

const CardShell = styled.div`
    background: rgba(10, 10, 30, 0.97);
    border-radius: 16px;
    border: 2px solid rgba(102, 126, 234, 0.5);
    backdrop-filter: blur(12px);
    padding: 20px 24px;
    color: white;
    min-width: 230px;
    max-width: 340px;
    box-shadow: 0 10px 30px rgba(0, 0, 0, 0.35);
    font-family: 'Nunito', sans-serif;
`;

const InlineCardShell = styled(CardShell)`
    display: block;
`;

const HoverCardShell = styled(CardShell)<{ $isOpen: boolean }>`
    z-index: 10;
    opacity: ${({ $isOpen }) => ($isOpen ? 1 : 0)};
    transform: ${({ $isOpen }) => ($isOpen ? 'translateY(0) scale(1)' : 'translateY(-8px) scale(0.98)')};
    transform-origin: top left;
    transition: opacity 0.2s ease, transform 0.2s ease;
    pointer-events: ${({ $isOpen }) => ($isOpen ? 'auto' : 'none')};
`;

const Content = styled.div`
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 8px;
`;

const AvatarImage = styled.img`
    width: 74px;
    height: 74px;
    border-radius: 50%;
    object-fit: cover;
    border: 2px solid rgba(255, 255, 255, 0.65);
    box-shadow: 0 0 15px rgba(102, 126, 234, 0.45);
    margin-bottom: 6px;
`;

const AvatarPlaceholder = styled.div`
    width: 74px;
    height: 74px;
    border-radius: 50%;
    margin-bottom: 6px;
    background: rgba(255, 255, 255, 0.08);
    border: 2px solid rgba(255, 255, 255, 0.25);
    display: grid;
    place-items: center;
    color: #b7bfd7;
    font-size: 2rem;
`;

const NameTitle = styled.h2`
    font-size: 1.08rem;
    margin: 0;
    text-align: center;
    line-height: 1.25;
    font-weight: 800;
    letter-spacing: 0.2px;
`;

const FallbackText = styled.span`
    color: #9da7c3;
`;

const EmailText = styled.p`
    font-size: 0.9rem;
    margin: 0;
    text-align: center;
    color: #d3ddff;
    max-width: 100%;
    overflow-wrap: anywhere;
`;

const EditButton = styled.button`
    margin-top: 10px;
    padding: 8px 16px;
    border-radius: 10px;
    border: 1px solid rgba(255, 255, 255, 0.15);
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
    font-size: 0.92rem;
    cursor: pointer;
    box-shadow: 0 5px 14px rgba(0, 0, 0, 0.2);
    transition: transform 0.16s ease, box-shadow 0.16s ease;

    &:hover {
        transform: translateY(-1px);
        box-shadow: 0 7px 16px rgba(0, 0, 0, 0.25);
    }
`;

const CardWrapper = styled.div`
    position: absolute;
    top: 58px;
    right: -80px;
    display: flex;
    flex-direction: row-reverse;
    align-items: flex-start;
    pointer-events: none;
`;

export default function ProfileCard({
    avatarUrl,
    username,
    email,
    inline = false,
    showEditButton = true,
    onEditClick,
    forceOpen,
}: Props) {
    const [isOpen, setIsOpen] = useState(false);
    const shouldOpen = isOpen || !!forceOpen;

    const renderProfileContent = () => (
        <Content>
            {avatarUrl ? (
                <AvatarImage
                    src={avatarUrl}
                    alt={username || 'Avatar'}
                />
            ) : (
                <AvatarPlaceholder>
                    👤
                </AvatarPlaceholder>
            )}

            <NameTitle>{username || <FallbackText>No name</FallbackText>}</NameTitle>

            <EmailText>{email || <FallbackText>No email</FallbackText>}</EmailText>

            {showEditButton && (
                <EditButton
                    type="button"
                    onClick={(event) => {
                        event.preventDefault();
                        event.stopPropagation();
                        if (onEditClick) {
                            onEditClick();
                            return;
                        }
                        alert('Edit Profile à implémenter !');
                    }}
                >
                    ✏️ Edit Profile
                </EditButton>
            )}
        </Content>
    );

    if (inline) {
        return (
            <InlineCardShell>{renderProfileContent()}</InlineCardShell>
        );
    }

    return (
        <CardWrapper
            onMouseEnter={() => setIsOpen(true)}
            onMouseLeave={() => setIsOpen(false)}
        >   
            <HoverCardShell $isOpen={shouldOpen}>
                {renderProfileContent()}
            </HoverCardShell>
        </CardWrapper>
    );
}