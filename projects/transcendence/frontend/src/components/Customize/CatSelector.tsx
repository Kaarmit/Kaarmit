import styled from 'styled-components';

type Props = {
    selected: string | null;
    onSelect: (value: string) => void;
};

const CAT_TYPES = [
    { id: 'beigecat', label: 'Beige', img: '/paw//cursor/beige.png' },
    { id: 'greycat', label: 'Grey', img: '/paw//cursor/grey.png' },
    { id: 'orangecat', label: 'Orange', img: '/paw//cursor/orange.png' },
    { id: 'whitecat', label: 'White', img: '/paw//cursor/white.png' },
];

const SelectorGrid = styled.div`
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(40px, 1fr));
    gap: 8px;
`;

const CatButton = styled.button<{ $selected: boolean }>`
    padding: 8px;
    height: clamp(56px, 12vw, 80px);
    border-radius: 8px;
    background: ${({ $selected }) => ($selected ? 'rgba(102,126,234,0.7)' : 'rgba(255,255,255,0.06)')};
    color: white;
    border: ${({ $selected }) => ($selected ? '3px solid white' : '2px solid rgba(255,255,255,0.2)')};
    box-shadow: ${({ $selected }) => ($selected ? '0 0 18px rgba(0,0,0,0.4)' : '0 4px 8px rgba(0,0,0,0.2)')};
    cursor: pointer;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 8px;
    transition: transform 0.15s ease, box-shadow 0.15s ease, background 0.15s ease, border-color 0.15s ease;

    &:hover {
        transform: translateY(-1px);
    }

    &:focus-visible {
        outline: 2px solid white;
        outline-offset: 2px;
    }
`;

const CatImage = styled.img`
    width: clamp(28px, 6vw, 36px);
    height: clamp(28px, 6vw, 36px);
    object-fit: contain;
    border-radius: 6px;
`;

export default function CatSelector({ selected, onSelect }: Props) {
    return (
        <SelectorGrid>
            {CAT_TYPES.map((cat) => {
                const isSelected = selected === cat.id;
                return (
                    <CatButton
                        key={cat.id}
                        onClick={() => onSelect(cat.id)}
                        onKeyDown={(e) => { if (e.key === 'Enter' || e.key === ' ') onSelect(cat.id); }}
                        aria-pressed={isSelected}
                        title={cat.label}
                        $selected={isSelected}
                    >
                        {cat.img ? (
                        <CatImage src={cat.img} alt={cat.label} />
                    ) : (
                        cat.label
                    )}
                    </CatButton>
                );
            })}
        </SelectorGrid>
    );
}