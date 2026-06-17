import { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import styled from 'styled-components';
import type { FriendPresence, User, FriendRequest } from '../../types';
import ProfileCard from '../Profile/ProfileCard';
import ToggleButton from '../ToggleButton';

interface Props {
    friends: FriendPresence[];
    onlineCount: number;
    isRealtimeConnected: boolean;
    loading: boolean;
    pendingRequests: FriendRequest[];
    outgoingRequests: number[];
    searchUsers: (query: string) => Promise<User[]>;
    addFriend: (user: User) => Promise<void>;
    acceptRequest: (requestId: number) => Promise<void>;
    refuseRequest: (requestId: number) => Promise<void>;
    removeFriend: (userId: number) => Promise<void>;
    openChatWithFriend: (friendId: number) => void;
}

const PanelShell = styled.div`
    position: absolute;
    top: clamp(80px, 15vw, 112px);
    right: clamp(8px, 3vw, 20px);
    z-index: 50;
    width: auto;
    max-width: 340px;
    display: flex;
    flex-direction: column;
    box-sizing: border-box;
    align-items: flex-end;
    pointer-events: none;
`;

const FriendsPanelCard = styled.div<{ $open: boolean }>`
    margin-top: 10px;
    background: rgba(10, 10, 30, 0.95);
    padding: 16px;
    border-radius: 20px;
    border: 2px solid rgba(102, 126, 234, 0.5);
    backdrop-filter: blur(12px);
    width: 420px;
    max-width: calc(100vw - 60px);
    max-height: 65vh;
    overflow-y: auto;
    box-shadow: 0 14px 40px rgba(0, 0, 0, 0.45);
    opacity: ${({ $open }) => ($open ? 1 : 0)};
    transform: ${({ $open }) => ($open ? 'translateY(0) scale(1)' : 'translateY(-8px) scale(0.98)')};
    transform-origin: top right;
    transition: opacity 0.2s ease, transform 0.2s ease;
    pointer-events: ${({ $open }) => ($open ? 'auto' : 'none')};
`;

const PanelHeader = styled.div`
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin-bottom: 12px;
`;

const PanelTitle = styled.h3`
    margin: 0;
    color: white;
    font-family: 'Press Start 2P', cursive;
    font-size: 0.65rem;
`;

const OnlineCount = styled.span`
    color: #bcd4ff;
    font-family: 'Nunito', sans-serif;
    font-size: 0.8rem;
    font-weight: 700;
`;

const Section = styled.div`
    margin-bottom: 12px;
`;

const SectionLabel = styled.div`
    color: #bcd4ff;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
`;

const RequestCard = styled.div`
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 8px 10px;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.06);
`;

const RequestActions = styled.div`
    display: flex;
    align-items: center;
    gap: 6px;
`;

const ActionButton = styled.button<{ $variant: 'accept' | 'decline' | 'add' | 'sent' | 'profile' | 'visit' | 'remove' | 'close' }>`
    border: none;
    border-radius: 10px;
    padding: 6px 10px;
    cursor: pointer;
    appearance: none;
    border: 1px solid transparent;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
    background: ${({ $variant }) => {
        switch ($variant) {
            case 'accept':
                return 'linear-gradient(135deg, #4CAF50 0%, #2e7d32 100%)';
            case 'decline':
            case 'remove':
            case 'close':
                return 'linear-gradient(135deg, #f44336 0%, #c62828 100%)';
            case 'add':
                return 'linear-gradient(135deg, #667eea 0%, #764ba2 100%)';
            case 'profile':
                return 'rgba(182, 141, 228, 0.24)';
            case 'visit':
                return 'rgba(235, 103, 247, 0.24)';
            case 'sent':
                return 'rgba(255, 255, 255, 0.12)';
            default:
                return 'rgba(255, 255, 255, 0.12)';
        }
    }};
    color: ${({ $variant }) => {
        switch ($variant) {
            case 'profile':
                return '#f4e9ff';
            case 'visit':
                return '#ffe4ff';
            case 'sent':
                return '#c2c7d3';
            default:
                return '#ffffff';
        }
    }};
    border-color: ${({ $variant }) => {
        switch ($variant) {
            case 'profile':
                return 'rgba(182, 141, 228, 0.6)';
            case 'visit':
                return 'rgba(235, 103, 247, 0.6)';
            case 'sent':
                return 'rgba(255, 255, 255, 0.14)';
            default:
                return 'transparent';
        }
    }};
    cursor: ${({ $variant }) => ($variant === 'sent' ? 'not-allowed' : 'pointer')};
    box-shadow: ${({ $variant }) => ($variant === 'sent' ? 'none' : '0 6px 14px rgba(0, 0, 0, 0.2)')};

    &:hover:not(:disabled) {
        transform: translateY(-1px);
        filter: brightness(1.08);
    }

    &:disabled {
        opacity: 0.75;
    }
`;

const SearchInput = styled.input`
    width: 100%;
    padding: 10px 12px;
    border-radius: 12px;
    border: 1px solid rgba(255, 255, 255, 0.2);
    background: rgba(255, 255, 255, 0.1);
    color: white;
    outline: none;
    font-family: 'Nunito', sans-serif;
    font-size: 0.9rem;
`;

const SearchResults = styled.div`
    margin-top: 8px;
    display: grid;
    gap: 6px;
`;

const ResultRow = styled.div`
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 8px 10px;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.06);
`;

const ResultText = styled.div`
    color: white;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
`;

const HelperText = styled.div`
    color: #c2c7d3;
    font-family: 'Nunito', sans-serif;
    font-size: 0.85rem;
    padding: 6px 2px;
`;

const ErrorHelperText = styled(HelperText)`
    color: #ff9fa1;
`;

const LoadingHelperText = styled(HelperText)`
    margin-bottom: 10px;
`;

const FriendsList = styled.div`
    display: grid;
    gap: 8px;
`;

const FriendRow = styled.div`
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 8px 10px;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.06);
`;

const FriendMeta = styled.div`
    display: flex;
    align-items: center;
    gap: 10px;
`;

const FriendName = styled.div`
    color: white;
    font-family: 'Nunito', sans-serif;
    font-weight: 700;
`;

const FriendStatus = styled.div`
    display: flex;
    align-items: center;
    gap: 6px;
`;

const StatusDot = styled.span<{ $online: boolean }>`
    width: 10px;
    height: 10px;
    border-radius: 50%;
    display: inline-block;
    background: ${({ $online }) => ($online ? '#4CAF50' : '#9aa0b3')};
    box-shadow: ${({ $online }) => ($online ? '0 0 8px #4CAF50' : 'none')};
`;

const StatusText = styled.span<{ $online: boolean }>`
    color: ${({ $online }) => ($online ? '#8ee88e' : '#c2c7d3')};
    font-family: 'Nunito', sans-serif;
    font-size: 0.78rem;
    font-weight: 700;
`;

const SelectedFriendSection = styled.div`
    margin-top: 12px;
    display: grid;
    gap: 8px;
    justify-items: center;
`;

const SelectedFriendHeader = styled.div`
    width: 100%;
    display: flex;
    justify-content: space-between;
    align-items: center;
`;

export default function FriendsPanel({
    friends,
    onlineCount,
    loading,
    pendingRequests,
    outgoingRequests,
    searchUsers,
    addFriend,
    acceptRequest,
    refuseRequest,
    removeFriend,
}: Props) {
    const navigate = useNavigate();
    const [isOpen, setIsOpen] = useState(false);
    const [search, setSearch] = useState('');
    const [searchResults, setSearchResults] = useState<User[]>([]);
    const [isSearching, setIsSearching] = useState(false);
    const [searchError, setSearchError] = useState<string | null>(null);
    const [selectedFriendId, setSelectedFriendId] = useState<number | null>(null);

    const selectedFriend = selectedFriendId
        ? friends.find((friend) => friend.id === selectedFriendId) ?? null
        : null;

    const friendIdSet = new Set(friends.map(f => f.id));
    const displayedSearchResults = search.trim() ? searchResults.filter(u => !friendIdSet.has(u.id)) : [];

useEffect(() => {
    let active = true;
    if (!search.trim()) {
        setSearchResults([]);
        setIsSearching(false);
        setSearchError(null);
        return;
    }
    setIsSearching(true);
    setSearchError(null);
    searchUsers(search.trim())
        .then(users => {
            if (active) setSearchResults(users);
        })
        .catch(() => {
            if (active) {
                setSearchResults([]);
                setSearchError('Cannot search for users right now');
            }
        })
        .finally(() => {
            if (active) setIsSearching(false);
        });
    return () => { active = false; };
}, [search, searchUsers]);

    return (
        <PanelShell>
            <ToggleButton
                isOpen={isOpen}
                onClick={() => setIsOpen((prev) => !prev)}
                label="Friends"
                badge={`${onlineCount}/${friends.length}`}
            />

            <FriendsPanelCard $open={isOpen}>
                <PanelHeader>
                    <PanelTitle>Friends</PanelTitle>

                    <OnlineCount>{onlineCount}/{friends.length} online</OnlineCount>
                </PanelHeader>

                {pendingRequests.length > 0 && (
                    <Section>
                        <SectionLabel>
                            Pending Friend Requests ({pendingRequests.length})
                        </SectionLabel>
                        {pendingRequests.map(request => (
                            <RequestCard
                                key={request.id}
                            >
                                <ResultText>
                                    {request.fromUser?.username ?? `User #${request.fromUserId}`}
                                </ResultText>
                                <RequestActions>
                                    <ActionButton
                                        onClick={() => { void acceptRequest(request.id); }}
                                        $variant="accept"
                                    >
                                        Accept
                                    </ActionButton>
                                    <ActionButton
                                        onClick={() => { void refuseRequest(request.id); }}
                                        $variant="decline"
                                    >
                                        Decline
                                    </ActionButton>
                                </RequestActions>
                            </RequestCard>
                        ))}
                    </Section>
                )}

                <Section>
                    <SearchInput
                        type="text"
                        value={search}
                        onChange={(event) => setSearch(event.target.value)}
                        placeholder="Find a friend (username)"
                    />

                    {search.trim() && (
                        <SearchResults>
                            {isSearching && (
                                <HelperText>
                                    Searching...
                                </HelperText>
                            )}

                            {!isSearching && searchError && (
                                <ErrorHelperText>
                                    {searchError}
                                </ErrorHelperText>
                            )}

                            {!isSearching && !searchError && displayedSearchResults.length === 0 && (
                                <HelperText>
                                    No results found or already friends
                                </HelperText>
                            )}

                            {!isSearching && displayedSearchResults.map(user => (
                                <ResultRow
                                    key={user.id}
                                >
                                    <ResultText>
                                        {user.username}
                                    </ResultText>
                                    {outgoingRequests.includes(user.id) ? (
                                        <ActionButton
                                            disabled
                                            $variant="sent"
                                        >
                                            Request sent
                                        </ActionButton>
                                    ) : (
                                        <ActionButton
                                            onClick={() => {
                                                // guard client-side against duplicates
                                                if (outgoingRequests.includes(user.id)) {
                                                    alert("You have already sent a friend request.");
                                                    return;
                                                }

                                                void addFriend(user);
                                                setSearch('');
                                                setSearchResults([]);
                                            }}
                                            $variant="add"
                                        >
                                            Add
                                        </ActionButton>
                                    )}
                                </ResultRow>
                            ))}
                        </SearchResults>
                    )}
                </Section>

                {loading && (
                    <LoadingHelperText>
                        Searching for friends...
                    </LoadingHelperText>
                )}

                <FriendsList>
                    {friends.map(friend => (
                        <FriendRow
                            key={friend.id}
                        >
                            <FriendMeta>
                                <FriendName>
                                    {friend.username}
                                </FriendName>
                                <ActionButton
                                    onClick={() => setSelectedFriendId(friend.id)}
                                    $variant="profile"
                                >
                                    Profile
                                </ActionButton>

                                <ActionButton
                                    onClick={() => navigate(`/nekotchi/${friend.id}`)}
                                    $variant="visit"
                                >
                                    Visit
                                </ActionButton>

                                <ActionButton
                                    onClick={() => { void removeFriend(friend.id); }}
                                    $variant="remove"
                                >
                                    ✘
                                </ActionButton>
                            </FriendMeta>

                            <FriendStatus>
                                <StatusDot $online={friend.isOnline} />
                                <StatusText $online={friend.isOnline}>
                                    {friend.isOnline ? 'Online' : 'Offline'}
                                </StatusText>
                            </FriendStatus>
                        </FriendRow>
                    ))}
                </FriendsList>

                {selectedFriend && (
                    <SelectedFriendSection>
                        <SelectedFriendHeader>
                            <SectionLabel>
                                {selectedFriend.username}
                            </SectionLabel>
                            <ActionButton
                                onClick={() => setSelectedFriendId(null)}
                                $variant="close"
                            >
                                ✘
                            </ActionButton>
                        </SelectedFriendHeader>
                        <ProfileCard
                            avatarUrl={selectedFriend.avatarUrl}
                            username={selectedFriend.username}
                            email={selectedFriend.email}
                            inline
                            showEditButton={false}
                        />
                    </SelectedFriendSection>
                )}
            </FriendsPanelCard>
        </PanelShell>
    );
}
