import styled from 'styled-components';

type Props = {
  selected: string | null;
  onSelect: (value: string) => void;
};

export type BackgroundOption = {
  id: number;
  name: string;
  image: string;
};

const backgroundOptions: BackgroundOption[] = [
  { id: 1, name: 'city', image: '/backgrounds/city.png' },
  { id: 2, name: 'forest', image: '/backgrounds/forest.jpg' },
  { id: 3, name: 'ocean', image: '/backgrounds/ocean.jpg' },
  { id: 4, name: 'space', image: '/backgrounds/space.png' },
  { id: 5, name: 'torigate', image: '/backgrounds/torigate.jpg' },
  { id: 6, name: 'sunset', image: '/backgrounds/sunset.jpg' },
];

const SelectorGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(40px, 1fr));
  gap: 8px;
`;

const BackgroundButton = styled.button<{ $selected: boolean; $image: string }>`
  height: clamp(56px, 14vw, 72px);
  border-radius: 10px;
  background-image: ${({ $image }) => `url(${$image})`};
  background-size: cover;
  background-position: center;
  border: ${({ $selected }) => ($selected ? '3px solid white' : '2px solid rgba(255,255,255,0.2)')};
  box-shadow: ${({ $selected }) => ($selected ? '0 0 18px rgba(255,255,255,0.35)' : '0 4px 10px rgba(0,0,0,0.25)')};
  cursor: pointer;
  overflow: hidden;
  position: relative;
  padding: 0;
  transition: transform 0.15s ease, box-shadow 0.15s ease, border-color 0.15s ease;

  &:hover {
    transform: translateY(-1px);
  }

  &:focus-visible {
    outline: 2px solid white;
    outline-offset: 2px;
  }
`;

export default function BackgroundSelector({ selected, onSelect }: Props) {
  return (
    <SelectorGrid>
      {backgroundOptions.map((bg) => {
        const isSelected = selected === bg.image;
        return (
          <BackgroundButton
            key={bg.id}
            onClick={() => onSelect(bg.image)}
            aria-pressed={isSelected}
            title={bg.name}
            $selected={isSelected}
            $image={bg.image}
          >
          </BackgroundButton>
        );
      })}
    </SelectorGrid>
  );
}