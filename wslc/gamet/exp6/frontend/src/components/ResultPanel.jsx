import './ResultPanel.css'

function ResultPanel({
  gameResult,
  verificationResult,
  mikeActionData,
  payoffMatrix,
  beliefs,
  onReset,
  onRetryWithPrior
}) {
  const isPBE = verificationResult?.pbe_established || false
  const pGun = verificationResult?.p_gun || 0

  return (
    <div className="result-panel-component">
      <div className="phase-header">
        <h2>🏆 游戏结果</h2>
        <p>查看本局结果和贝叶斯验证</p>
      </div>

      {/* 游戏结果展示 */}
      <div className="result-cards">
        {/* 真实状态揭示 */}
        <div className="result-card reveal-card">
          <h3>🔮 真相揭示</h3>
          <div className="reveal-content">
            <div className="reveal-item">
              <span className="reveal-label">自然设定</span>
              <span className="reveal-value">
                P(持枪) = {(verificationResult?.p_gun * 100 || 0).toFixed(1)}%
              </span>
            </div>
            <div className="reveal-item highlight">
              <span className="reveal-label">迈克实际状态</span>
              <span className={`reveal-badge ${gameResult.actual_state}`}>
                {gameResult.actual_state === 'gun' ? '🔫 持枪' : '✋ 空手'}
              </span>
            </div>
          </div>
        </div>

        {/* 行动结果 */}
        <div className="result-card action-card">
          <h3>⚔️ 对决结果</h3>
          <div className="action-summary">
            <div className="action-row">
              <span className="player-name">🎩 迈克</span>
              <span className="player-action">{gameResult.mike_action_cn}</span>
            </div>
            <div className="action-row">
              <span className="player-name">🔪 杀手</span>
              <span className="player-action">{gameResult.killer_action_cn}</span>
            </div>
          </div>
        </div>

        {/* 收益结果 */}
        <div className={`result-card payoff-card ${gameResult.winner}`}>
          <h3>💰 收益结算</h3>
          <div className="payoff-display">
            <div className="payoff-row">
              <span>迈克收益</span>
              <span className={`payoff-value ${gameResult.mike_payoff >= 0 ? 'positive' : 'negative'}`}>
                {gameResult.mike_payoff >= 0 ? '+' : ''}{gameResult.mike_payoff}
              </span>
            </div>
            <div className="payoff-row">
              <span>杀手收益</span>
              <span className={`payoff-value ${gameResult.killer_payoff >= 0 ? 'positive' : 'negative'}`}>
                {gameResult.killer_payoff >= 0 ? '+' : ''}{gameResult.killer_payoff}
              </span>
            </div>
          </div>
          <div className="winner-display">
            {gameResult.winner === 'mike' && '🎩 迈克获胜!'}
            {gameResult.winner === 'killer' && '🔪 杀手获胜!'}
            {gameResult.winner === 'tie' && '🤝 平局!'}
          </div>
        </div>
      </div>

      {/* 贝叶斯验证 */}
      <div className={`verification-section ${isPBE ? 'success' : 'failure'}`}>
        <h3>🔬 贝叶斯验证</h3>
        <div className="verification-summary">
          <div className={`verification-badge ${isPBE ? 'success' : 'failure'}`}>
            {isPBE ? '✅ 完美贝叶斯均衡成立' : '❌ 信念与后验不一致'}
          </div>
          <p className="verification-message">{verificationResult?.summary}</p>
        </div>

        <div className="verification-details">
          <h4>📊 详细验证</h4>
          <div className="detail-grid">
            {Object.entries(verificationResult?.details || {}).map(([action, detail]) => (
              <div key={action} className={`detail-card ${detail.on_path ? (detail.match ? 'match' : 'mismatch') : 'off-path'}`}>
                <div className="detail-header">
                  <span className="detail-action">
                    {action === 'guard' ? '🛡️ 把守' : '🏃 躲避'}
                  </span>
                  <span className={`detail-status ${detail.on_path ? (detail.match ? 'match' : 'mismatch') : 'off-path'}`}>
                    {!detail.on_path ? '路径外' : (detail.match ? '一致' : '不一致')}
                  </span>
                </div>
                {detail.on_path ? (
                  <div className="detail-content">
                    <div className="detail-row">
                      <span>贝叶斯后验 P(持枪|{action === 'guard' ? '把守' : '躲避'})</span>
                      <span className="detail-value">{(detail.posterior_gun || 0).toFixed(4)}</span>
                    </div>
                    <div className="detail-row">
                      <span>您的信念</span>
                      <span className="detail-value">{(detail.player_belief_gun || 0).toFixed(4)}</span>
                    </div>
                    <div className="detail-row">
                      <span>该行动概率 P({action === 'guard' ? '把守' : '躲避'})</span>
                      <span className="detail-value">{(detail.p_action || 0).toFixed(4)}</span>
                    </div>
                  </div>
                ) : (
                  <div className="detail-content">
                    <p className="off-path-message">{detail.message}</p>
                  </div>
                )}
              </div>
            ))}
          </div>
        </div>

        {!isPBE && (
          <div className="failure-note">
            <p>
              <strong>⚠️ 注意：</strong>
              您的信念与贝叶斯后验概率不一致。即便本局获胜，也可能是纯属侥幸。
              建议重新设定信念，寻找真正的完美贝叶斯均衡。
            </p>
          </div>
        )}

        {isPBE && (
          <div className="success-note">
            <p>
              <strong>🎉 恭喜！</strong>
              您成功建立了完美贝叶斯均衡！您的信念与理性推断完全一致。
            </p>
          </div>
        )}
      </div>

      {/* 操作按钮 */}
      <div className="action-section">
        <button
          className="reset-btn continue"
          onClick={() => onReset(true)}
        >
          🔄 保持设置，再来一局
        </button>
        <button
          className="reset-btn retry-prior"
          onClick={() => onRetryWithPrior(pGun)}
          title={`将信念设为 P(持枪)=${pGun.toFixed(4)}，保持先验再来一局`}
        >
          🎯 用真实先验作为信念重试
        </button>
        <button
          className="reset-btn new-game"
          onClick={() => onReset(false)}
        >
          🆕 重新设置，开始新游戏
        </button>
      </div>
    </div>
  )
}

export default ResultPanel
