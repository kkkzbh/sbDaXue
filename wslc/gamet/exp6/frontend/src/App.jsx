import { useState, useCallback } from 'react'
import PayoffMatrix from './components/PayoffMatrix'
import BeliefInput from './components/BeliefInput'
import GameFlow from './components/GameFlow'
import ResultPanel from './components/ResultPanel'
import PresetButtons from './components/PresetButtons'
import { createGame, setPayoff, setBeliefs, getMikeAction, submitKillerAction, getResult, resetGame } from './api'
import './App.css'

// 游戏阶段
const PHASES = {
  SETUP: 'setup',           // 设置阶段：输入收益矩阵和信念
  MIKE_ACTION: 'mike_action', // 迈克行动阶段
  KILLER_ACTION: 'killer_action', // 杀手行动阶段
  RESULT: 'result'          // 结果阶段
}

function App() {
  // 游戏状态
  const [gameId, setGameId] = useState(null)
  const [phase, setPhase] = useState(PHASES.SETUP)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)
  
  // 游戏数据
  const [payoffMatrix, setPayoffMatrix] = useState(null)
  const [beliefs, setBeliefState] = useState(null)
  const [mikeActionData, setMikeActionData] = useState(null)
  const [gameResult, setGameResult] = useState(null)
  const [verificationResult, setVerificationResult] = useState(null)
  const [currentPreset, setCurrentPreset] = useState(null)

  // 选择预设
  const handleSelectPreset = useCallback((presetKey, payoff, belief) => {
    setPayoffMatrix(payoff)
    setBeliefState(belief)
    setCurrentPreset(presetKey)
  }, [])

  // 创建新游戏
  const handleStartGame = useCallback(async (payoff, belief) => {
    setLoading(true)
    setError(null)
    
    try {
      // 1. 创建游戏
      const createRes = await createGame(
        currentPreset === 'semi_separating' ? { prior_gun: 0.5 } : {}
      )
      const newGameId = createRes.game_id
      setGameId(newGameId)
      
      // 2. 设置收益矩阵
      await setPayoff(newGameId, payoff)
      setPayoffMatrix(payoff)
      
      // 3. 设置信念
      await setBeliefs(newGameId, belief)
      setBeliefState(belief)
      
      // 4. 获取迈克行动
      const mikeRes = await getMikeAction(newGameId)
      setMikeActionData(mikeRes)
      
      setPhase(PHASES.KILLER_ACTION)
    } catch (err) {
      setError(err.message || '游戏初始化失败')
    } finally {
      setLoading(false)
    }
  }, [currentPreset])

  // 杀手行动
  const handleKillerAction = useCallback(async (action) => {
    if (!gameId) return
    
    setLoading(true)
    setError(null)
    
    try {
      // 1. 提交杀手行动
      const result = await submitKillerAction(gameId, action)
      setGameResult(result)
      
      // 2. 获取贝叶斯验证结果
      const verification = await getResult(gameId)
      setVerificationResult(verification)
      
      setPhase(PHASES.RESULT)
    } catch (err) {
      setError(err.message || '提交行动失败')
    } finally {
      setLoading(false)
    }
  }, [gameId])

  // 重置游戏
  const handleReset = useCallback(async (keepSettings = false) => {
    setLoading(true)
    setError(null)

    try {
      if (gameId && keepSettings) {
        // 重置当前游戏
        await resetGame(gameId)
        const mikeRes = await getMikeAction(gameId)
        setMikeActionData(mikeRes)
        setGameResult(null)
        setVerificationResult(null)
        setPhase(PHASES.KILLER_ACTION)
      } else {
        // 完全重新开始
        setGameId(null)
        setPayoffMatrix(null)
        setBeliefState(null)
        setMikeActionData(null)
        setGameResult(null)
        setVerificationResult(null)
        setPhase(PHASES.SETUP)
      }
    } catch (err) {
      setError(err.message || '重置失败')
    } finally {
      setLoading(false)
    }
  }, [gameId])

  // 用真实先验作为信念重试（用于实现成功的混同均衡）
  const handleRetryWithPrior = useCallback(async (pGun) => {
    if (!gameId) return

    setLoading(true)
    setError(null)

    try {
      // 1. 将信念设置为真实先验
      const newBeliefs = {
        guard_gun: pGun.toFixed(6),
        hide_gun: pGun.toFixed(6)
      }

      // 2. 更新后端信念
      await setBeliefs(gameId, newBeliefs)
      setBeliefState(newBeliefs)

      // 3. 重置游戏（保持 p_gun 不变）
      await resetGame(gameId)

      // 4. 获取迈克行动
      const mikeRes = await getMikeAction(gameId)
      setMikeActionData(mikeRes)

      setGameResult(null)
      setVerificationResult(null)
      setPhase(PHASES.KILLER_ACTION)
    } catch (err) {
      setError(err.message || '重试失败')
    } finally {
      setLoading(false)
    }
  }, [gameId])

  return (
    <div className="app">
      <header className="app-header">
        <h1>🎯 刺杀博弈</h1>
        <p className="subtitle">不完全信息博弈 · 完美贝叶斯均衡</p>
      </header>

      {error && (
        <div className="error-banner">
          <span>⚠️ {error}</span>
          <button onClick={() => setError(null)}>×</button>
        </div>
      )}

      <main className="app-main">
        {phase === PHASES.SETUP && (
          <div className="setup-phase">
            <div className="phase-header">
              <h2>📋 游戏设置</h2>
              <p>设置收益矩阵和杀手信念，开始一局新游戏</p>
            </div>

            <PresetButtons
              onSelectPreset={handleSelectPreset}
              currentPreset={currentPreset}
            />

            <div className="setup-container">
              <PayoffMatrix
                onPayoffChange={(p) => { setPayoffMatrix(p); }}
                initialPayoff={payoffMatrix}
              />
              
              <BeliefInput 
                onBeliefChange={setBeliefState}
                initialBelief={beliefs}
              />
              
              <button 
                className="start-button"
                onClick={() => handleStartGame(payoffMatrix, beliefs)}
                disabled={loading || !payoffMatrix || !beliefs}
              >
                {loading ? '初始化中...' : '🎮 开始游戏'}
              </button>
            </div>
          </div>
        )}

        {phase === PHASES.KILLER_ACTION && mikeActionData && (
          <GameFlow 
            mikeActionData={mikeActionData}
            onKillerAction={handleKillerAction}
            loading={loading}
            beliefs={beliefs}
          />
        )}

        {phase === PHASES.RESULT && gameResult && verificationResult && (
          <ResultPanel
            gameResult={gameResult}
            verificationResult={verificationResult}
            mikeActionData={mikeActionData}
            payoffMatrix={payoffMatrix}
            beliefs={beliefs}
            onReset={handleReset}
            onRetryWithPrior={handleRetryWithPrior}
          />
        )}
      </main>

      <footer className="app-footer">
        <p>实验6：不完全信息博弈建模 | 博弈论实验</p>
      </footer>
    </div>
  )
}

export default App
