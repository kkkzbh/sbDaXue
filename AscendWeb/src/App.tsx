import './App.css';
import KnowledgeGraph from './components/KnowledgeGraph';
import { StudentProvider } from './contexts/StudentContext';

function App() {
  return (
    <StudentProvider>
      <div style={{ width: '100vw', height: '100vh', background: '#272727' }}>
        <KnowledgeGraph />
      </div>
    </StudentProvider>
  );
}

export default App;
