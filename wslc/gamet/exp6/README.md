# 实验6：不完全信息博弈建模 - 刺杀博弈游戏

## 📖 实验简介

本实验基于《教父》中迈克医院救父的情节，实现了一个**完全但不完美信息博弈**的游戏系统。玩家扮演杀手，与计算机扮演的迈克进行博弈。

### 博弈结构

- **自然**: 随机决定迈克是否持枪（概率分布对玩家不公开）
- **迈克**: 根据状态选择"把守"或"躲避"
- **杀手**: 观察迈克行动后，选择"刺杀"或"离开"

### 核心概念

1. **逆向归纳法**: 从杀手的最优反应开始，反向计算迈克的均衡策略
2. **贝叶斯更新**: 杀手观察到迈克的行动后更新对其状态的信念
3. **完美贝叶斯均衡**: 信念与策略相互一致的均衡

## 🚀 快速开始

### 环境要求

- Python 3.8+
- Node.js 16+
- npm 或 yarn

### 一键启动

```bash
chmod +x run.sh
./run.sh
```

### 手动启动

#### 后端

```bash
cd backend
pip install fastapi uvicorn pydantic
python -m uvicorn main:app --reload --port 21447
```

#### 前端

```bash
cd frontend
npm install
npm run dev
```

### 访问

- 前端界面: http://localhost:5173
- API 文档: http://localhost:21447/docs

## 📁 项目结构

```
exp6/
├── backend/
│   ├── main.py              # FastAPI 入口
│   ├── bayesian_game_.py    # 核心博弈逻辑
│   ├── schemas.py           # Pydantic 模型
│   └── tests/
│       └── test_bayesian_game.py
├── frontend/
│   ├── src/
│   │   ├── App.jsx          # 主应用组件
│   │   ├── App.css          # 全局样式
│   │   ├── api.js           # API 服务
│   │   ├── main.jsx         # 入口文件
│   │   └── components/
│   │       ├── PayoffMatrix.jsx   # 收益矩阵输入
│   │       ├── BeliefInput.jsx    # 信念输入
│   │       ├── GameFlow.jsx       # 游戏流程
│   │       └── ResultPanel.jsx    # 结果展示
│   ├── index.html
│   ├── package.json
│   └── vite.config.js
├── problem/
│   └── question.md          # 实验要求
├── run.sh                   # 一键启动脚本
└── README.md
```

## 🎮 游戏流程

1. **设置收益矩阵**: 玩家设定两种状态（持枪/空手）下各策略组合的收益
2. **设置杀手信念**: 输入条件概率 P(持枪|把守) 和 P(持枪|躲避)
3. **开始游戏**: 系统计算均衡策略，迈克做出行动
4. **杀手决策**: 玩家观察迈克行动后选择"刺杀"或"离开"
5. **结果展示**: 显示实际状态、收益结算和贝叶斯验证

## 🔬 API 接口

| 端点 | 方法 | 功能 |
|------|------|------|
| `/game/new` | POST | 创建新游戏 |
| `/game/{id}/payoff` | POST | 设置收益矩阵 |
| `/game/{id}/beliefs` | POST | 设置杀手信念 |
| `/game/{id}/mike-action` | GET | 获取迈克行动 |
| `/game/{id}/killer-action` | POST | 提交杀手决策 |
| `/game/{id}/result` | GET | 获取贝叶斯验证结果 |
| `/game/{id}/reset` | POST | 重置游戏 |

## 🧪 运行测试

```bash
cd backend
python -m pytest tests/ -v
```

## 📝 实验报告要点

1. **收益矩阵设计**: 如何设计收益使博弈有意义
2. **信念设定**: 不同信念对均衡的影响
3. **贝叶斯验证**: 理解信念一致性的含义
4. **完美贝叶斯均衡**: 找到使信念与后验一致的均衡

## 💡 提示

- 信念输入支持分数格式（如 `2/3`）和小数格式（如 `0.667`）
- 即使获胜，如果信念与后验不一致，说明判断存在偏差
- 尝试不同的收益矩阵和信念设定，观察均衡变化

## 📚 参考资料

- 完美贝叶斯均衡 (Perfect Bayesian Equilibrium)
- 逆向归纳法 (Backward Induction)
- 信号博弈 (Signaling Games)
