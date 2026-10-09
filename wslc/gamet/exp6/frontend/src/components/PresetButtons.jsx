import './PresetButtons.css'

// 五种实验预设
const PRESETS = {
  separating: {
    name: '分离均衡',
    description: '持枪把守、空手躲避，PBE成立',
    payoff: {
      gun: {
        guard: { kill: { mike: 1, killer: -10 }, leave: { mike: 4, killer: 0 } },
        hide: { kill: { mike: 0, killer: 2 }, leave: { mike: 1, killer: 0 } }
      },
      empty: {
        guard: { kill: { mike: -5, killer: 2 }, leave: { mike: -2, killer: 0 } },
        hide: { kill: { mike: -1, killer: 2 }, leave: { mike: 0, killer: 0 } }
      }
    },
    beliefs: { guard_gun: '1', hide_gun: '0' }
  },
  pooling_base: {
    name: '混同策略基础',
    description: '都选把守，用于测试混同均衡（需信念=先验才成立）',
    payoff: {
      gun: {
        guard: { kill: { mike: 2, killer: -2 }, leave: { mike: 5, killer: 0 } },
        hide: { kill: { mike: 0, killer: 1 }, leave: { mike: 1, killer: 0 } }
      },
      empty: {
        guard: { kill: { mike: 0, killer: 1 }, leave: { mike: 3, killer: 0 } },
        hide: { kill: { mike: -2, killer: 2 }, leave: { mike: -1, killer: 0 } }
      }
    },
    beliefs: { guard_gun: '0.5', hide_gun: '0.5' }
  },
  pooling_bias: {
    name: '混同策略(偏差)',
    description: '都选把守，但信念与先验不一致',
    payoff: {
      gun: {
        guard: { kill: { mike: 2, killer: -2 }, leave: { mike: 5, killer: 0 } },
        hide: { kill: { mike: 0, killer: 1 }, leave: { mike: 1, killer: 0 } }
      },
      empty: {
        guard: { kill: { mike: 0, killer: 1 }, leave: { mike: 3, killer: 0 } },
        hide: { kill: { mike: -2, killer: 2 }, leave: { mike: -1, killer: 0 } }
      }
    },
    beliefs: { guard_gun: '0.8', hide_gun: '0.2' }
  },
  belief_mismatch: {
    name: '信念不一致',
    description: '故意设置错误信念，展示验证失败',
    payoff: {
      gun: {
        guard: { kill: { mike: 2, killer: -2 }, leave: { mike: 3, killer: 0 } },
        hide: { kill: { mike: 0, killer: 1 }, leave: { mike: 1, killer: 0 } }
      },
      empty: {
        guard: { kill: { mike: -1, killer: 2 }, leave: { mike: 1, killer: 0 } },
        hide: { kill: { mike: -2, killer: 3 }, leave: { mike: 0, killer: 0 } }
      }
    },
    beliefs: { guard_gun: '0.9', hide_gun: '0.1' }
  },
  semi_separating: {
    name: '半分离均衡',
    description: '空手状态混合策略（固定先验 P(持枪)=0.5），信念与后验一致',
    payoff: {
      gun: {
        guard: { kill: { mike: 2, killer: -2 }, leave: { mike: 5, killer: 0 } },
        hide: { kill: { mike: 0, killer: 1 }, leave: { mike: 1, killer: 0 } }
      },
      empty: {
        guard: { kill: { mike: 0, killer: 2 }, leave: { mike: 2, killer: 0 } },
        hide: { kill: { mike: 2, killer: 2 }, leave: { mike: 2, killer: 0 } }
      }
    },
    beliefs: { guard_gun: '2/3', hide_gun: '0' }
  }
}

function PresetButtons({ onSelectPreset, currentPreset }) {
  return (
    <div className="preset-buttons-component">
      <div className="preset-header">
        <h3>快速预设</h3>
        <span className="preset-hint">点击按钮自动填充收益矩阵和信念</span>
      </div>
      <div className="preset-grid">
        {Object.entries(PRESETS).map(([key, preset]) => (
          <button
            key={key}
            className={`preset-btn ${currentPreset === key ? 'active' : ''}`}
            onClick={() => onSelectPreset(key, preset.payoff, preset.beliefs)}
            title={preset.description}
          >
            <span className="preset-name">{preset.name}</span>
            <span className="preset-desc">{preset.description}</span>
          </button>
        ))}
      </div>
    </div>
  )
}

export default PresetButtons
