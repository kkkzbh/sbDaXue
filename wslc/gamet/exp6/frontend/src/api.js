/**
 * API 服务 - 与后端 FastAPI 通信
 */

const API_BASE = 'http://localhost:21447'

/**
 * 通用请求函数
 */
async function request(endpoint, options = {}) {
  const url = `${API_BASE}${endpoint}`
  
  const config = {
    headers: {
      'Content-Type': 'application/json',
    },
    ...options,
  }
  
  try {
    const response = await fetch(url, config)
    
    if (!response.ok) {
      const error = await response.json().catch(() => ({ detail: '请求失败' }))
      throw new Error(error.detail || `HTTP ${response.status}`)
    }
    
    return await response.json()
  } catch (error) {
    if (error.message.includes('Failed to fetch')) {
      throw new Error('无法连接到服务器，请确保后端已启动')
    }
    throw error
  }
}

/**
 * 创建新游戏
 */
export async function createGame(options = {}) {
  const { seed = null, prior_gun = null } = options || {}
  const body = {}
  if (seed !== null && seed !== undefined) body.seed = seed
  if (prior_gun !== null && prior_gun !== undefined) body.prior_gun = prior_gun
  return request('/game/new', {
    method: 'POST',
    body: JSON.stringify(body),
  })
}

/**
 * 设置收益矩阵
 */
export async function setPayoff(gameId, payoff) {
  return request(`/game/${gameId}/payoff`, {
    method: 'POST',
    body: JSON.stringify(payoff),
  })
}

/**
 * 设置杀手信念
 */
export async function setBeliefs(gameId, beliefs) {
  return request(`/game/${gameId}/beliefs`, {
    method: 'POST',
    body: JSON.stringify(beliefs),
  })
}

/**
 * 获取迈克行动
 */
export async function getMikeAction(gameId) {
  return request(`/game/${gameId}/mike-action`, {
    method: 'GET',
  })
}

/**
 * 提交杀手行动
 */
export async function submitKillerAction(gameId, action) {
  return request(`/game/${gameId}/killer-action`, {
    method: 'POST',
    body: JSON.stringify({ action }),
  })
}

/**
 * 获取贝叶斯验证结果
 */
export async function getResult(gameId) {
  return request(`/game/${gameId}/result`, {
    method: 'GET',
  })
}

/**
 * 获取均衡策略摘要
 */
export async function getEquilibrium(gameId) {
  return request(`/game/${gameId}/equilibrium`, {
    method: 'GET',
  })
}

/**
 * 重置游戏
 */
export async function resetGame(gameId, seed = null) {
  const body = seed !== null ? { seed } : {}
  return request(`/game/${gameId}/reset`, {
    method: 'POST',
    body: JSON.stringify(body),
  })
}

/**
 * 删除游戏
 */
export async function deleteGame(gameId) {
  return request(`/game/${gameId}`, {
    method: 'DELETE',
  })
}

export default {
  createGame,
  setPayoff,
  setBeliefs,
  getMikeAction,
  submitKillerAction,
  getResult,
  getEquilibrium,
  resetGame,
  deleteGame,
}
