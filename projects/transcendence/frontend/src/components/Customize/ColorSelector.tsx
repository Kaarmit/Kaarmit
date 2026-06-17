import styled from 'styled-components';

type Props = {
    selected: string | null;
    onSelect: (value: string) => void;
};

const COLORS = ['#FF69B4', '#4169E1', '#ad8df3', '#7AE8A8', '#FF4444', '#F4A97A', '#F5E87A', '#FFFFFF'];

const SelectorGrid = styled.div`
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(25px, 1fr));
    gap: 8px;
`;

const ColorButton = styled.button<{ $selected: boolean; $color: string }>`
    height: clamp(28px, 6vw, 35px);
    border-radius: 10px;
    background: ${({ $color }) => $color};
    border: ${({ $selected }) => ($selected ? '3px solid white' : '2px solid rgba(255,255,255,0.2)')};
    box-shadow: ${({ $selected, $color }) => ($selected ? `0 0 18px ${$color}` : '0 4px 8px rgba(0,0,0,0.2)')};
    cursor: pointer;
    transition: transform 0.12s, box-shadow 0.12s, border-color 0.12s;
    outline: none;
    padding: 0;

    &:hover {
        transform: translateY(-1px);
    }

    &:focus-visible {
        outline: 2px solid white;
        outline-offset: 2px;
    }
`;

export default function ColorSelector({ selected, onSelect }: Props) {
    return (
        <SelectorGrid>
            {COLORS.map((color) => {
                const isSelected = selected === color;
                return (
                    <ColorButton
                        key={color}
                        onClick={() => onSelect(color)}
                        onKeyDown={(e) => { if (e.key === 'Enter' || e.key === ' ') onSelect(color); }}
                        aria-pressed={isSelected}
                        title={color}
                        $selected={isSelected}
                        $color={color}
                    />
                );
            })}
        </SelectorGrid>
    );
}