import { Link } from 'react-router-dom';
import Footer from '../components/Layout/Footer';

function PrivacyPolicy() {
  return (
    <>
      <main className="legal-page">
        <section className="legal-card">
          <h1>Privacy Policy</h1>

          <p>
            Nekotchi 3D is a student project created as part of the 42 curriculum.
            This Privacy Policy explains what data may be collected and how it is used
            inside the application.
          </p>

          <h2>1. Data We Collect</h2>
          <p>
            The application may store account information such as username, email
            address, hashed password, avatar, friend relationships, chat messages,
            Nekotchi customization choices, and gameplay-related data.
          </p>

          <h2>2. Authentication Data</h2>
          <p>
            Passwords are hashed before being stored. The application uses JWT tokens
            for authentication. If Two-Factor Authentication is enabled, a 2FA secret
            is stored securely in the database to verify temporary authentication codes.
          </p>

          <h2>3. Chat and Social Features</h2>
          <p>
            Messages, conversations, friend requests, online status and profile data
            may be stored or processed to provide real-time multiplayer and social
            features.
          </p>

          <h2>4. How Data Is Used</h2>
          <p>
            Data is used only to run the application features: authentication, profile
            management, friend system, chat, Nekotchi customization, mini-games and
            real-time multiplayer interactions.
          </p>

          <h2>5. Data Storage</h2>
          <p>
            Application data is stored in a PostgreSQL database managed through Prisma
            ORM. Environment variables are used for sensitive configuration values.
          </p>

          <h2>6. Security</h2>
          <p>
            The project uses HTTPS, password hashing, protected routes and token-based
            authentication. However, Nekotchi 3D remains an educational project and
            should not be used to store sensitive personal information.
          </p>

          <h2>7. User Rights</h2>
          <p>
            Users may update their profile information from the application. Data
            deletion or export features may be handled by the project team during the
            evaluation or development process.
          </p>

          <h2>8. Contact</h2>
          <p>
            For questions about this project, please contact the development team.
          </p>

          <Link to="/">Back to home</Link>
        </section>
      </main>
      <Footer />
    </>
  );
}

export default PrivacyPolicy;
