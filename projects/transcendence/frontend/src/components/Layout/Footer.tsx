import styled from 'styled-components';
import { Link } from 'react-router-dom';

const FooterContainer = styled.footer`
  width: 100%;
  padding: 16px;
  display: flex;
  justify-content: center;
  gap: 24px;
  border-top: 1px solid rgba(255, 255, 255, 0.1);
  margin-top: 40px;

  a {
    color: #0066cc;
    text-decoration: none;
    font-size: 0.875rem;
    transition: color 0.2s ease;

    &:hover {
      color: #0052a3;
    }
  }
`;

function Footer() {
  return (
    <FooterContainer>
      <Link to="/privacy">Privacy Policy</Link>
      <Link to="/terms">Terms of Service</Link>
    </FooterContainer>
  );
}

export default Footer;
