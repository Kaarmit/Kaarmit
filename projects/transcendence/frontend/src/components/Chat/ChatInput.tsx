import { useEffect, useRef, useState } from 'react';
import styled from 'styled-components';
import { useChat } from '../../hooks/useChat';
import ChatBubble from './ChatBubble';
import type { FriendPresence } from '../../types';

interface Props {
    friends: FriendPresence[];
    friendToOpenId?: number | null;
    friendToOpenSignal?: number;
    currentUserId?: number;
    currentUsername?: string;
}

const ChatLauncher = styled.div`
        position: fixed;
        bottom: 12px;
        right: 12px;
        z-index: 40;
        pointer-events: none;

        @media (max-width: 480px) {
            bottom: 8px;
            right: 8px;
        }
`;

const ChatLauncherButton = styled.button`
    width: 60px;
    height: 60px;
    border-radius: 50%;
    border: none;
    background: linear-gradient(135deg, #000003 0%, #171579 100%);
    color: white;
    font-size: 1.8rem;
    cursor: pointer;
    box-shadow: 0 4px 20px rgba(102, 126, 234, 0.4);
    display: grid;
    place-items: center;
    padding: 0;
    pointer-events: auto;
`;

const ChatLauncherIcon = styled.img`
    width: 30px;
    height: 30px;
    object-fit: contain;
`;

const FriendSelector = styled.div`
    margin-top: 10px;
    width: 260px;
    max-height: 320px;
    overflow-y: auto;
    background: rgba(10, 10, 30, 0.95);
    border: 1px solid rgba(255, 255, 255, 0.15);
    border-radius: 14px;
    padding: 10px;
    display: grid;
    gap: 8px;
    backdrop-filter: blur(10px);
    pointer-events: auto;
`;

const EmptyState = styled.div`
    color: #c2c7d3;
    font-family: 'Nunito', sans-serif;
`;

const FriendEntryButton = styled.button`
    border: none;
    border-radius: 10px;
    padding: 8px 10px;
    cursor: pointer;
    background: rgba(255, 255, 255, 0.08);
    color: white;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
    text-align: left;
    display: flex;
    justify-content: space-between;
    align-items: center;
`;

const FriendOnlineText = styled.span<{ $online: boolean }>`
    color: ${({ $online }) => ($online ? '#8ee88e' : '#c2c7d3')};
    font-size: 0.8rem;
`;

const ChatWindow = styled.div<{ $rightOffset: number; $minimized: boolean; $zIndex: number }>`
        position: fixed;
        bottom: 20px;
        right: ${({ $rightOffset }) => `${$rightOffset}px`};
        width: 320px;
        height: ${({ $minimized }) => ($minimized ? '50px' : '430px')};
        background: rgba(26, 26, 46, 0.95);
        border-radius: 16px;
        box-shadow: 0 10px 40px rgba(0, 0, 0, 0.5);
        display: flex;
        flex-direction: column;
        overflow: hidden;
        backdrop-filter: blur(10px);
        border: 1px solid rgba(255, 255, 255, 0.1);
        z-index: ${({ $zIndex }) => $zIndex};

        @media (max-width: 480px) {
            left: 12px;
            right: 12px;
            width: calc(100% - 24px);
            bottom: 12px;
            /* smaller height for mobile */
            height: ${({ $minimized }) => ($minimized ? '48px' : '50vh')};
            max-height: 50vh;
            border-radius: 12px;
        }
`;

const ChatHeader = styled.div<{ $minimized: boolean }>`
    padding: 12px;
    background: linear-gradient(135deg, #091455 0%, #000000 100%);
    color: white;
    font-weight: bold;
    font-size: 0.95rem;
    display: flex;
    align-items: center;
    gap: 8px;
    cursor: pointer;
`;

const ChatTitle = styled.span`
    color: white;
    font-size: 0.64rem;
    font-family: 'Press Start 2P', cursive;
    font-weight: 700;
`;

const ChatStatus = styled.span<{ $online: boolean }>`
    color: ${({ $online }) => ($online ? '#d5ffd5' : '#ecb5b5')};
    font-size: 0.72rem;
`;

const HeaderIconButton = styled.button`
    background: rgba(255, 255, 255, 0.2);
    border: none;
    color: white;
    font-size: 1rem;
    width: 24px;
    height: 24px;
    border-radius: 50%;
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    margin-left: auto;
`;

const MessagesList = styled.div`
    flex: 1;
    overflow-y: auto;
    padding: 12px;
    display: flex;
    flex-direction: column;
`;

const InputRow = styled.div`
    padding: 10px;
    border-top: 1px solid rgba(255, 255, 255, 0.1);
    display: flex;
    gap: 8px;
`;

const ChatInputField = styled.input`
    flex: 1;
    padding: 8px 12px;
    border-radius: 20px;
    border: none;
    background: rgba(255, 255, 255, 0.1);
    color: white;
    outline: none;
    font-size: 0.88rem;
`;

const SendButton = styled.button<{ $active: boolean }>`
    padding: 8px 14px;
    border-radius: 20px;
    border: none;
    background: ${({ $active }) => ($active ? 'linear-gradient(135deg, #667eea 0%, #764ba2 100%)' : 'rgba(255,255,255,0.1)')};
    color: white;
    cursor: ${({ $active }) => ($active ? 'pointer' : 'not-allowed')};
    font-weight: bold;
`;

export default function ChatPanel({
    friends,
    friendToOpenId = null,
    friendToOpenSignal = 0,
    currentUserId,
    currentUsername,
}: Props) {
    const chatHook = useChat(
        currentUserId ?? 0,
        currentUsername ?? 'You',
    );
    const { messagesByFriend, draftByFriend, setNewMessage, sendMessage } = chatHook;

    const [isSelectorOpen, setIsSelectorOpen] = useState(false);
    const [openFriendIds, setOpenFriendIds] = useState<number[]>([]);
    const [minimizedFriendIds, setMinimizedFriendIds] = useState<number[]>([]);
    const messagesEndRefs = useRef<Record<number, HTMLDivElement | null>>({});
    const [windowWidth, setWindowWidth] = useState<number>(typeof window !== 'undefined' ? window.innerWidth : 1024);

    // open automatically if a friend ID is passed via props (e.g. from Chat button in FriendList)
    useEffect(() => {
        if (!friendToOpenId) return;
        setOpenFriendIds((prev) =>
            prev.includes(friendToOpenId) ? prev : [...prev, friendToOpenId]
        );
        setMinimizedFriendIds((prev) => prev.filter((id) => id !== friendToOpenId));
    }, [friendToOpenId, friendToOpenSignal]);

    // cleanup if a friend is removed from the list
    useEffect(() => {
        setOpenFriendIds((prev) => prev.filter((id) => friends.some((f) => f.id === id)));
        setMinimizedFriendIds((prev) => prev.filter((id) => friends.some((f) => f.id === id)));
    }, [friends]);

    useEffect(() => {
        function onResize() {
            setWindowWidth(window.innerWidth);
        }
        window.addEventListener('resize', onResize);
        return () => window.removeEventListener('resize', onResize);
    }, []);

    // scroll automatically to bottom when a new message arrives
    useEffect(() => {
        openFriendIds.forEach((friendId) => {
            messagesEndRefs.current[friendId]?.scrollIntoView({ behavior: 'smooth' });
        });
    }, [messagesByFriend, openFriendIds]);

    // open a chat window AND initialize the backend conversation
    const openConversation = (friendId: number) => {
        console.log('[ChatInput] openConversation appelé pour friendId:', friendId);
        setOpenFriendIds((prev) => (prev.includes(friendId) ? prev : [...prev, friendId]));
        setMinimizedFriendIds((prev) => prev.filter((id) => id !== friendId));
        setIsSelectorOpen(false);
        // backend call : POST /conversations + conversation:join + load history
        chatHook.openConversation(friendId);
    };

    const closeConversation = (friendId: number) => {
        setOpenFriendIds((prev) => prev.filter((id) => id !== friendId));
        setMinimizedFriendIds((prev) => prev.filter((id) => id !== friendId));
    };

    const toggleMinimizeConversation = (friendId: number) => {
        setMinimizedFriendIds((prev) =>
            prev.includes(friendId)
                ? prev.filter((id) => id !== friendId)
                : [...prev, friendId]
        );
    };

    const openFriendsAll = openFriendIds
        .map((id) => friends.find((f) => f.id === id))
        .filter((f): f is FriendPresence => Boolean(f));

    const isSmallScreen = windowWidth <= 480;
    const openFriends = isSmallScreen
        ? (openFriendsAll.length ? [openFriendsAll[openFriendsAll.length - 1]] : [])
        : openFriendsAll;

    return (
        <>
            <ChatLauncher>
                <ChatLauncherButton
                    onClick={() => setIsSelectorOpen((prev) => !prev)}
                    title="Chat"
                >
                    <ChatLauncherIcon
                        src="/icons/letter.gif"
                        alt="Chat"
                    />
                </ChatLauncherButton>

                {isSelectorOpen && (
                    <FriendSelector>
                        {friends.length === 0 && (
                            <EmptyState>
                                Aucun ami disponible.
                            </EmptyState>
                        )}
                        {friends.map((friend) => (
                            <FriendEntryButton
                                type="button"
                                key={friend.id}
                                onClick={() => openConversation(friend.id)}
                            >
                                <span>{friend.username}</span>
                                <FriendOnlineText $online={friend.isOnline}>
                                    {friend.isOnline ? 'Online' : 'Offline'}
                                </FriendOnlineText>
                            </FriendEntryButton>
                        ))}
                    </FriendSelector>
                )}
            </ChatLauncher>

            {openFriends.map((friend, index) => {
                const messages = messagesByFriend[friend.id] ?? [];
                const draft = draftByFriend[friend.id] ?? '';
                const isMinimized = minimizedFriendIds.includes(friend.id);

                return (
                    <ChatWindow
                        key={friend.id}
                        $rightOffset={isSmallScreen ? 12 : 95 + (index * 340)}
                        $minimized={isMinimized}
                        $zIndex={35 + index}
                    >
                        <ChatHeader
                            onClick={() => {
                                toggleMinimizeConversation(friend.id);
                            }}
                            $minimized={isMinimized}
                            title={isMinimized ? 'Restore' : 'Minimize'}
                        >
                            <ChatTitle>
                                💌 {friend.username}
                            </ChatTitle>
                            <ChatStatus $online={friend.isOnline}>
                                {friend.isOnline ? 'On' : 'Off'}
                            </ChatStatus>
                            <HeaderIconButton type="button" onClick={(e) => { e.stopPropagation(); closeConversation(friend.id); }}>
                                ✘
                            </HeaderIconButton>
                        </ChatHeader>

                        {!isMinimized && (
                            <>
                                <MessagesList>
                                    {messages.map((msg) => (
                                        <ChatBubble
                                            key={msg.id}
                                            message={msg}
                                            isOwn={msg.userId === (currentUserId ?? 0)}
                                        />
                                    ))}
                                    <div ref={(node) => { messagesEndRefs.current[friend.id] = node; }} />
                                </MessagesList>

                                <InputRow>
                                    <ChatInputField
                                        type="text"
                                        value={draft}
                                        onChange={(e) => setNewMessage(friend.id, e.target.value)}
                                        onKeyDown={(e) => {
                                            if (e.key === 'Enter' && !e.shiftKey) {
                                                e.preventDefault();
                                                sendMessage(friend.id);
                                            }
                                        }}
                                        placeholder={`Message to ${friend.username}...`}
                                    />
                                    <SendButton
                                        type="button"
                                        onClick={() => { void sendMessage(friend.id, draft); }}
                                        disabled={!draft.trim()}
                                        $active={Boolean(draft.trim())}
                                    >
                                        Send
                                    </SendButton>
                                </InputRow>
                            </>
                        )}
                    </ChatWindow>
                );
            })}
        </>
    );
}