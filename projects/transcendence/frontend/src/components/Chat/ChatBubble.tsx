import type { ChatMessage } from '../../types';
import styled from 'styled-components';

interface Props {
  message: ChatMessage;
  isOwn: boolean;
}

const BubbleWrapper = styled.div<{ $isOwn: boolean }>`
  display: flex;
  flex-direction: column;
  align-items: ${({ $isOwn }) => ($isOwn ? 'flex-end' : 'flex-start')};
  margin-bottom: 12px;
  animation: slideIn 0.3s ease-out;
`;

const Username = styled.div<{ $isOwn: boolean }>`
  font-size: 0.72rem;
  color: #df99d0;
  margin-bottom: 4px;
  padding-left: ${({ $isOwn }) => ($isOwn ? '0' : '8px')};
  padding-right: ${({ $isOwn }) => ($isOwn ? '8px' : '0')};
  font-family: 'Nunito', sans-serif;
  font-weight: 700;
`;

const MessageBubble = styled.div<{ $isOwn: boolean }>`
  max-width: 70%;
  padding: 10px 12px;
  border-radius: 14px;
  background: ${({ $isOwn }) => ($isOwn ? 'rgba(102, 126, 234, 0.22)' : 'rgba(255,255,255,0.08)')};
  border: 1px solid ${({ $isOwn }) => ($isOwn ? 'rgba(102, 126, 234, 0.55)' : 'rgba(255,255,255,0.2)')};
  backdrop-filter: blur(10px);
  color: white;
  word-wrap: break-word;
  box-shadow: 0 6px 20px rgba(0, 0, 0, 0.25);
  font-family: 'Nunito', sans-serif;
  font-weight: 600;
  font-size: 0.9rem;
`;

const Timestamp = styled.div<{ $isOwn: boolean }>`
  font-size: 0.65rem;
  color: #c2c7d3;
  margin-top: 4px;
  padding-left: ${({ $isOwn }) => ($isOwn ? '0' : '8px')};
  padding-right: ${({ $isOwn }) => ($isOwn ? '8px' : '0')};
  font-family: 'Nunito', sans-serif;
`;

export default function ChatBubble({ message, isOwn }: Props) {
  return (
    <BubbleWrapper $isOwn={isOwn}>
      <Username $isOwn={isOwn}>{message.username}</Username>

      <MessageBubble $isOwn={isOwn}>{message.message}</MessageBubble>

      <Timestamp $isOwn={isOwn}>
        {new Date(message.timestamp).toLocaleTimeString('fr-FR', {
          hour: '2-digit',
          minute: '2-digit',
        })}
      </Timestamp>
    </BubbleWrapper>
  );
}