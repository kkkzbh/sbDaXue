import { useState, useEffect } from 'react'
import './PayoffMatrix.css'

// 默认收益矩阵（教父情节相关）
const DEFAULT_PAYOFF = {
  gun: {
    guard: { kill: { mike: 2, killer: -2 }, leave: { mike: 3, killer: 0 } },
    hide: { kill: { mike: 0, killer: 1 }, leave: { mike: 1, killer: 0 } }
  },
  empty: {
    guard: { kill: { mike: -1, killer: 2 }, leave: { mike: 1, killer: 0 } },
    hide: { kill: { mike: -2, killer: 3 }, leave: { mike: 0, killer: 0 } }
  }
}

const STATE_LABELS = {
  gun: '持枪 🔫',
  empty: '空手 ✋'
}

const MIKE_ACTION_LABELS = {
  guard: '把守',
  hide: '躲避'
}

const KILLER_ACTION_LABELS = {
  kill: '刺杀',
  leave: '离开'
}

function PayoffMatrix({ onPayoffChange, initialPayoff }) {
  const [payoff, setPayoff] = useState(initialPayoff || DEFAULT_PAYOFF)

  // 当外部传入的 initialPayoff 变化时，更新内部状态
  useEffect(() => {
    if (initialPayoff) {
      setPayoff(initialPayoff)
    }
  }, [initialPayoff])

  useEffect(() => {
    onPayoffChange(payoff)
  }, [payoff, onPayoffChange])

  const handlePayoffChange = (state, mikeAction, killerAction, player, value) => {
    const numValue = parseFloat(value) || 0
    setPayoff(prev => ({
      ...prev,
      [state]: {
        ...prev[state],
        [mikeAction]: {
          ...prev[state][mikeAction],
          [killerAction]: {
            ...prev[state][mikeAction][killerAction],
            [player]: numValue
          }
        }
      }
    }))
  }

  const renderMatrix = (state) => (
    <div className="matrix-container" key={state}>
      <h3>{STATE_LABELS[state]}</h3>
      <table className="payoff-table">
        <thead>
          <tr>
            <th></th>
            <th colSpan="2">杀手行动</th>
          </tr>
          <tr>
            <th>迈克行动</th>
            <th>{KILLER_ACTION_LABELS.kill}</th>
            <th>{KILLER_ACTION_LABELS.leave}</th>
          </tr>
        </thead>
        <tbody>
          {['guard', 'hide'].map(mikeAction => (
            <tr key={mikeAction}>
              <td className="action-label">{MIKE_ACTION_LABELS[mikeAction]}</td>
              {['kill', 'leave'].map(killerAction => (
                <td key={killerAction} className="payoff-cell">
                  <div className="payoff-inputs">
                    <div className="input-group">
                      <label>M:</label>
                      <input
                        type="number"
                        value={payoff[state][mikeAction][killerAction].mike}
                        onChange={(e) => handlePayoffChange(state, mikeAction, killerAction, 'mike', e.target.value)}
                        step="0.1"
                      />
                    </div>
                    <div className="input-group">
                      <label>K:</label>
                      <input
                        type="number"
                        value={payoff[state][mikeAction][killerAction].killer}
                        onChange={(e) => handlePayoffChange(state, mikeAction, killerAction, 'killer', e.target.value)}
                        step="0.1"
                      />
                    </div>
                  </div>
                </td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
      <p className="matrix-note">M = 迈克收益, K = 杀手收益</p>
    </div>
  )

  const handleReset = () => {
    setPayoff(DEFAULT_PAYOFF)
  }

  return (
    <div className="payoff-matrix-component">
      <div className="section-header">
        <h2>📊 收益矩阵</h2>
        <button className="reset-btn" onClick={handleReset}>重置默认值</button>
      </div>
      <p className="section-desc">
        设置两种状态（持枪/空手）下的收益矩阵。每个单元格包含 (迈克收益, 杀手收益)。
      </p>
      <div className="matrices">
        {['gun', 'empty'].map(state => renderMatrix(state))}
      </div>
    </div>
  )
}

export default PayoffMatrix
