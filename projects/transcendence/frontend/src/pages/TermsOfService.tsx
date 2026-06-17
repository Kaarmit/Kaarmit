import { Link } from 'react-router-dom';
import Footer from '../components/Layout/Footer';

function TermsOfService() {
  return (
    <>
      <main className="legal-page">
        <section className="legal-card">
          <h1>Terms of Service</h1>

          <p>
            Nekotchi 3D is an educational web application created as part of the 42
            curriculum. By using the application, users agree to follow these basic
            terms and community rules.
          </p>

          <h2>1. Purpose of the Application</h2>
          <p>
            Nekotchi 3D is a multiplayer virtual pet experience with mini-games,
            customization, user profiles, friends and real-time chat features.
          </p>

          <h2>2. User Accounts</h2>
          <p>
            Users are responsible for keeping their account credentials secure. They
            must not share their password or attempt to access another user&apos;s account.
          </p>

          <h2>3. User Conduct</h2>
          <p>
            Users must not use the chat, profile system or multiplayer features to
            harass, insult, spam, impersonate others or share inappropriate content.
          </p>

          <h2>4. Fair Play</h2>
          <p>
            Users must not exploit bugs, manipulate network behavior, cheat in
            mini-games or intentionally disrupt the experience of other players.
          </p>

          <h2>5. User Content</h2>
          <p>
            Users are responsible for the messages, usernames, avatars and profile
            information they submit. The project team may remove inappropriate content
            during development or evaluation.
          </p>

          <h2>6. Availability</h2>
          <p>
            Nekotchi 3D is a student project. The application may contain bugs,
            temporary downtime, unfinished features or balancing issues.
          </p>

          <h2>7. Security</h2>
          <p>
            The project implements authentication, protected routes, HTTPS and optional
            Two-Factor Authentication. Users should still avoid storing sensitive
            personal information in the application.
          </p>

          <h2>8. Changes to These Terms</h2>
          <p>
            These terms may be updated as the project evolves.
          </p>

          <Link to="/">Back to home</Link>
        </section>
      </main>
      <Footer />
    </>
  );
}

export default TermsOfService;
