import { useState, useEffect } from 'react'
import './BeliefInput.css'

const DEFAULT_BELIEFS = {
  guard_gun: '2/3',
  hide_gun: '0'
}

function BeliefInput({ onBeliefChange, initialBelief }) {
  const [beliefs, setBeliefs] = useState(initialBelief || DEFAULT_BELIEFS)
  const [errors, setErrors] = useState({})

  // 当外部传入的 initialBelief 变化时，更新内部状态
  useEffect(() => {
    if (initialBelief) {
      setBeliefs(initialBelief)
    }
  }, [initialBelief])

  useEffect(() => {
    // 验证并更新父组件
    const newErrors = {}
    let valid = true

    for (const [key, value] of Object.entries(beliefs)) {
      const parsed = parseValue(value)
      if (parsed === null || parsed < 0 || parsed > 1) {
        newErrors[key] = '概率须在 [0, 1] 范围内'
        valid = false
      }
    }

    const guardValue = parseValue(beliefs.guard_gun)
    const hideValue = parseValue(beliefs.hide_gun)
    if (guardValue !== null && hideValue !== null) {
      const sum = guardValue + hideValue
      if (sum > 1 + 1e-9) {
        newErrors.guard_gun = 'P(持枪|把守) + P(持枪|躲避) 不能超过 1'
        newErrors.hide_gun = 'P(持枪|把守) + P(持枪|躲避) 不能超过 1'
        valid = false
      }
    }

    setErrors(newErrors)
    if (valid) {
      onBeliefChange(beliefs)
    } else {
      onBeliefChange(null)
    }
  }, [beliefs, onBeliefChange])

  const parseValue = (value) => {
    if (!value || value.trim() === '') return null
    const v = value.trim()
    
    if (v.includes('/')) {
      const parts = v.split('/')
      if (parts.length !== 2) return null
      const num = parseFloat(parts[0])
      const denom = parseFloat(parts[1])
      if (isNaN(num) || isNaN(denom) || denom === 0) return null
      return num / denom
    }
    
    const parsed = parseFloat(v)
    return isNaN(parsed) ? null : parsed
  }

  const getDisplayValue = (value) => {
    const parsed = parseValue(value)
    if (parsed === null) return '-'
    return parsed.toFixed(4)
  }

  const normalizeBeliefPair = (nextBeliefs) => {
    const guardValue = parseValue(nextBeliefs.guard_gun)
    const hideValue = parseValue(nextBeliefs.hide_gun)

    if (guardValue === null && hideValue === null) {
      return nextBeliefs
    }

    if (guardValue !== null && hideValue === null) {
      const complement = Math.max(0, Math.min(1, 1 - guardValue))
      return { ...nextBeliefs, hide_gun: complement.toFixed(4) }
    }

    if (guardValue === null && hideValue !== null) {
      const complement = Math.max(0, Math.min(1, 1 - hideValue))
      return { ...nextBeliefs, guard_gun: complement.toFixed(4) }
    }

    if (guardValue !== null && hideValue !== null) {
      const sum = guardValue + hideValue
      if (sum > 1 + 1e-9) {
        // 保证不超过 1，保持当前输入值，给出错误提示即可
        return nextBeliefs
      }
    }

    return nextBeliefs
  }

  const handleChange = (key, value) => {
    const nextBeliefs = { ...beliefs, [key]: value }
    setBeliefs(normalizeBeliefPair(nextBeliefs))
  }

  const handleReset = () => {
    setBeliefs(DEFAULT_BELIEFS)
  }

  return (
    <div className="belief-input-component">
      <div className="section-header">
        <h2>🎯 杀手信念</h2>
        <button className="reset-btn" onClick={handleReset}>重置默认值</button>
      </div>
      <p className="section-desc">
        输入杀手对迈克状态的条件概率信念。支持分数（如 2/3）和小数（如 0.667）格式。
      </p>

      <div className="belief-cards">
        <div className={`belief-card ${errors.guard_gun ? 'error' : ''}`}>
          <div className="belief-header">
            <span className="belief-icon">🛡️</span>
            <span className="belief-title">把守时</span>
          </div>
          <div className="belief-formula">
            P(持枪 | 把守) = 
          </div>
          <div className="belief-input-wrapper">
            <input
              type="text"
              value={beliefs.guard_gun}
              onChange={(e) => handleChange('guard_gun', e.target.value)}
              placeholder="如: 2/3 或 0.667"
            />
          </div>
          <div className="belief-computed">
            计算值: {getDisplayValue(beliefs.guard_gun)}
          </div>
          <div className="belief-complement">
            P(空手 | 把守) = {(1 - (parseValue(beliefs.guard_gun) || 0)).toFixed(4)}
          </div>
          {errors.guard_gun && (
            <div className="belief-error">{errors.guard_gun}</div>
          )}
        </div>

        <div className={`belief-card ${errors.hide_gun ? 'error' : ''}`}>
          <div className="belief-header">
            <span className="belief-icon">🏃</span>
            <span className="belief-title">躲避时</span>
          </div>
          <div className="belief-formula">
            P(持枪 | 躲避) = 
          </div>
          <div className="belief-input-wrapper">
            <input
              type="text"
              value={beliefs.hide_gun}
              onChange={(e) => handleChange('hide_gun', e.target.value)}
              placeholder="如: 1/3 或 0.333"
            />
          </div>
          <div className="belief-computed">
            计算值: {getDisplayValue(beliefs.hide_gun)}
          </div>
          <div className="belief-complement">
            P(空手 | 躲避) = {(1 - (parseValue(beliefs.hide_gun) || 0)).toFixed(4)}
          </div>
          {errors.hide_gun && (
            <div className="belief-error">{errors.hide_gun}</div>
          )}
        </div>
      </div>

      <div className="belief-note">
        <strong>💡 提示：</strong>
        信念代表杀手看到迈克的行动后，对迈克真实状态的判断。
        这是两个独立的条件概率，不要求相加为 1。
        游戏结束后会验证您的信念是否与贝叶斯后验概率一致。
      </div>
    </div>
  )
}

export default BeliefInput
