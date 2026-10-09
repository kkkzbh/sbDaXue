import './GameFlow.css'

function GameFlow({ mikeActionData, onKillerAction, loading, beliefs }) {
  const actionCn = mikeActionData?.action_cn || '未知'
  const action = mikeActionData?.mike_action || ''
  const condProbs = mikeActionData?.conditional_probs || {}
  const killerResponse = mikeActionData?.killer_response_info || {}

  // 获取当前行动对应的杀手最优反应
  const currentResponse = killerResponse[action] || {}
  const probKey = action === 'guard' ? 'P(guard|state)' : 'P(hide|state)'
  const pActionGivenState = condProbs[probKey] ?? 0

  return (
    <div className="game-flow-component">
      <div className="phase-header">
        <h2>🎬 第一阶段：迈克行动</h2>
        <p>迈克已经做出决策，现在轮到杀手选择行动</p>
      </div>

      <div className="game-board">
        {/* 迈克行动展示 */}
        <div className="mike-section">
          <div className="character-card mike">
            <div className="character-icon">🎩</div>
            <div className="character-name">迈克</div>
            <div className="character-role">（计算机）</div>
          </div>
          
          <div className="action-display">
            <div className="action-label">迈克选择了</div>
            <div className={`action-badge ${action}`}>
              {action === 'guard' ? '🛡️' : '🏃'} {actionCn}
            </div>
          </div>

          <div className="probability-info">
            <h4>📊 条件概率</h4>
            <div className="prob-list">
              <div className="prob-item">
                P({actionCn}|当前状态) = {pActionGivenState.toFixed(4)}
              </div>
            </div>
          </div>
        </div>

        {/* 分割线 */}
        <div className="versus">VS</div>

        {/* 杀手行动选择 */}
        <div className="killer-section">
          <div className="character-card killer">
            <div className="character-icon">🔪</div>
            <div className="character-name">杀手</div>
            <div className="character-role">（您）</div>
          </div>

          <div className="decision-panel">
            <h3>🎯 做出您的选择</h3>
            
            <div className="strategy-hint">
              <h4>💡 最优反应分析</h4>
              <div className="hint-content">
                <p>
                  当迈克选择<strong>{actionCn}</strong>时，根据您的信念：
                </p>
                <ul>
                  <li>E(刺杀) = {currentResponse.E_kill?.toFixed(4) || '-'}</li>
                  <li>E(离开) = {currentResponse.E_leave?.toFixed(4) || '-'}</li>
                </ul>
                <p className="hint-result">
                  {currentResponse.type === 'pure' ? (
                    <>最优策略: <strong>{currentResponse.action === 'kill' ? '刺杀' : '离开'}</strong></>
                  ) : (
                    <>无差异，可混合策略</>
                  )}
                </p>
              </div>
            </div>

            <div className="action-buttons">
              <button 
                className="action-btn kill"
                onClick={() => onKillerAction('kill')}
                disabled={loading}
              >
                <span className="btn-icon">⚔️</span>
                <span className="btn-text">刺杀</span>
                <span className="btn-desc">发动攻击</span>
              </button>

              <button 
                className="action-btn leave"
                onClick={() => onKillerAction('leave')}
                disabled={loading}
              >
                <span className="btn-icon">🚪</span>
                <span className="btn-text">离开</span>
                <span className="btn-desc">放弃行动</span>
              </button>
            </div>

            {loading && (
              <div className="loading-indicator">
                正在处理...
              </div>
            )}
          </div>
        </div>
      </div>

      <div className="belief-reminder">
        <h4>📝 您的信念设定</h4>
        <div className="belief-values">
          <span>P(持枪|把守) = {beliefs?.guard_gun || '-'}</span>
          <span>P(持枪|躲避) = {beliefs?.hide_gun || '-'}</span>
        </div>
      </div>
    </div>
  )
}

export default GameFlow
