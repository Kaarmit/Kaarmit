import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import { useAuth } from './hooks/useAuth';
import type { ReactNode } from 'react'; // React types for children prop, it represents any valid React child (string, element, fragment, etc.) and what needs to be rendered inside the PublicRoute component.
import Home from './pages/Home';
import Nekotchi from './pages/Nekotchi';
import GameSelectPage from './pages/GameSelectPage';
import CustomizePage from './pages/CustomizePage';
import FoodCatchGame from './games/FoodCatch';
import CourseGame from './games/Course';
import LoginPage from './components/Auth/LoginPage';
import RegisterPage from './components/Auth/RegisterPage';
import ProtectedRoute from './components/Auth/ProtectedRoute';
import EditProfile from './components/Auth/EditProfile';
import PrivacyPolicy from './pages/PrivacyPolicy';
import TermsOfService from './pages/TermsOfService';


function PublicRoute({ children }: { children: ReactNode }) {
  const { isAuthenticated, loading } = useAuth();
  if (loading) return null;
  if (isAuthenticated) return <Navigate to="/nekotchi/me" replace />;
  return <>{children}</>;
}

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Home />} />

        <Route
          path="/nekotchi/me"
          element={
            <ProtectedRoute>
              <Nekotchi />
            </ProtectedRoute>
          }
        />

        <Route
          path="/nekotchi/:userId"
          element={
            <ProtectedRoute>
              <Nekotchi />
            </ProtectedRoute>
          }
        />

        <Route
          path="/games"
          element={
            <ProtectedRoute>
              <GameSelectPage />
            </ProtectedRoute>
          }
        />

        <Route
          path="/minigame/food-catch"
          element={
            <ProtectedRoute>
              <FoodCatchGame />
            </ProtectedRoute>
          }
        />

        <Route
          path="/minigame/course"
          element={
            <ProtectedRoute>
              <CourseGame />
            </ProtectedRoute>
          }
        />

        <Route
          path="/customize"
          element={
            <ProtectedRoute>
              <CustomizePage />
            </ProtectedRoute>
          }
        />

        <Route
          path="/edit-profile"
          element={
            <ProtectedRoute>
              <EditProfile />
            </ProtectedRoute>
          }
        />

        <Route
          path="/editprofile"
          element={<Navigate to="/edit-profile" replace />}
        />

        <Route
          path="/update-profile"
          element={<Navigate to="/edit-profile" replace />}
        />
        <Route 
          path="/login" 
          element={
            <PublicRoute>
              <LoginPage />
            </PublicRoute>
          } 
        />
          <Route
            path="/register"
            element={
              <PublicRoute>
                <RegisterPage />
              </PublicRoute>
            }
        />
        
        <Route path="/privacy" element={<PrivacyPolicy />} />
        <Route path="/terms" element={<TermsOfService />} />

        <Route path="*" element={<Navigate to="/" replace />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;