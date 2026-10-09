# Ascend API 集成使用文档

本文档介绍 AscendWeb 与 Ascend Django 后端 API 的集成方案，包括配置、使用方法和视觉效果说明。

---

## 目录

- [概述](#概述)
- [快速开始](#快速开始)
- [配置说明](#配置说明)
- [功能特性](#功能特性)
- [API 接口](#api-接口)
- [组件说明](#组件说明)
- [知识点映射](#知识点映射)
- [故障排除](#故障排除)

---

## 概述

本集成实现了以下核心功能：

| 功能 | 描述 |
|------|------|
| **掌握度亮度映射** | 标签球亮度与学生知识点掌握度关联 |
| **薄弱知识点雷电特效** | 低掌握度的核心标签显示动态雷电环绕效果 |
| **学习路径激光流** | API 计算的学习路径以有向激光流形式连接标签 |

### 架构图

```
┌─────────────────┐     HTTP/JSON      ┌──────────────────┐
│  Ascend Django  │◄──────────────────►│    AscendWeb     │
│     API         │                     │   React + D3     │
└─────────────────┘                     └──────────────────┘
       │                                        │
       ▼                                        ▼
 ┌───────────────┐                    ┌──────────────────┐
 │ API 端点       │                    │   新增组件        │
 │ - /mastery/*  │                    │ - StudentContext │
 │ - /path/plan  │                    │ - PathConnectors │
 └───────────────┘                    │ - LightningEffect│
                                      └──────────────────┘
```

---

## 快速开始

### 1. 环境配置

复制环境变量模板并配置 API 地址：

```bash
cp .env.example .env
```

编辑 `.env` 文件：

```env
VITE_API_BASE=http://localhost:8000/api
```

### 2. 启动服务

```bash
# 终端 1: 启动 Ascend API
cd /home/kkkzbh/code/Ascend
uv run python manage.py runserver

# 终端 2: 启动 AscendWeb
cd /home/kkkzbh/code/AscendWeb
npm run dev
```

### 3. 访问应用

在浏览器中访问：

```
http://localhost:5173/?studentId=your_student_id
```

将 `your_student_id` 替换为实际的学生标识。注意：在 Ascend 数据中，该值通常是学生的 `nickname`（姓名/昵称）。

---

## 配置说明

### 环境变量

| 变量名 | 默认值 | 描述 |
|--------|--------|------|
| `VITE_API_BASE` | `http://localhost:8000/api` | Ascend API 基础地址 |

### URL 参数

| 参数 | 类型 | 描述 |
|------|------|------|
| `studentId` | string | 学生标识（通常为 `nickname`），用于获取个性化数据 |

**示例：**
```
http://localhost:5173/?studentId=test_student
http://localhost:5173/?studentId=12345
```

---

## 功能特性

### 1. 掌握度亮度映射

标签球的亮度根据学生对该知识点的掌握程度动态调整：

```
亮度 = 0.3 + 掌握度 × 0.7
发光强度 = 掌握度 × 0.5
```

| 掌握度 | 亮度 | 视觉效果 |
|--------|------|----------|
| 0% | 30% | 暗淡，几乎不发光 |
| 50% | 65% | 中等亮度 |
| 100% | 100% | 明亮，强烈发光 |

### 2. 薄弱知识点雷电特效

当某个知识点被 API 标记为薄弱点时，该标签球周围会显示动态雷电环绕效果：

- **颜色**: 蓝白色 (`#4da6ff`)
- **动画**: 闪烁 + 路径抖动
- **滤镜**: `lightningGlow` 发光效果

### 3. 学习路径激光流

API 返回的学习路径会以激光流形式可视化：

- **颜色**: 青色到蓝色渐变 (`#00ffff` → `#0040ff`)
- **动画**: 粒子沿路径流动
- **方向**: 箭头标记指示学习顺序
- **显示条件**: 仅在主视图（未选中任何标签）时显示

---

## API 接口

### 获取学生掌握度

```typescript
POST /api/mastery/knowledge-points
```

**请求体示例：**

```json
{
  "student": "<studentId>",
  "include_recommendations": true,
  "include_hierarchy": true,
  "weak_point_threshold": 0.6
}
```

说明：`student` 的值通常传学生的 `nickname`（与页面 URL 里的 `studentId` 一致）。后端也会兼容接收 `student_id`（历史字段名）。

**响应格式：**

```json
{
  "knowledge_mastery": {
    "基本概念": { "mastery": 0.8, "level": "熟练" },
    "线性结构": { "mastery": 0.5, "level": "一般" },
    "树": { "mastery": 0.3, "level": "薄弱" }
  },
  "weak_points": ["树", "图"],
  "summary": {
    "overall_mastery": 0.6
  }
}
```

### 获取学习路径

```typescript
POST /api/path/plan
```

**请求体示例：**

```json
{
  "student": "<studentId>",
  "top_n_targets": 5,
  "min_evidence": 1,
  "include_mastered": false,
  "mastered_threshold": 0.8,
  "attempt_penalty_alpha": 0.15
}
```

**响应格式：**

```json
{
  "targets": ["动态规划", "图"],
  "path": ["基本概念", "线性结构", "树", "图", "动态规划"]
}
```

---

## 组件说明

### StudentContext

学生数据状态管理 Context，提供以下数据：

```typescript
interface StudentState {
  studentId: string | null;      // 当前学生ID
  masteryMap: Record<string, number>;  // 标签ID → 掌握度
  weakPoints: string[];          // 薄弱知识点ID列表
  learningPath: string[];        // 学习路径（标签ID顺序）
  loading: boolean;              // 加载状态
  error: string | null;          // 错误信息
  overallMastery: number;        // 整体掌握度
}
```

**使用示例：**

```tsx
import { useStudent } from '../contexts/StudentContext';

function MyComponent() {
  const { masteryMap, weakPoints, loading } = useStudent();

  if (loading) return <div>加载中...</div>;

  return (
    <div>
      {Object.entries(masteryMap).map(([tagId, mastery]) => (
        <div key={tagId}>
          {tagId}: {(mastery * 100).toFixed(0)}%
          {weakPoints.includes(tagId) && ' ⚡ 薄弱点'}
        </div>
      ))}
    </div>
  );
}
```

### PathConnectors

学习路径连接线组件，渲染激光流效果：

```tsx
<PathConnectors
  gRef={svgGroupRef}
  learningPath={['basic', 'linear', 'tree']}
  tagPositions={positionsMap}
  visible={true}
/>
```

### LightningEffect

雷电环绕效果组件：

```tsx
<LightningEffect
  cx={100}        // 中心X坐标
  cy={100}        // 中心Y坐标
  radius={50}     // 环绕半径
  color="#4da6ff" // 雷电颜色
  intensity={1}   // 强度 (0-1)
/>
```

---

## 知识点映射

API 返回的知识点名称与前端标签ID的对应关系：

| API 知识点名称 | Web 标签 ID |
|---------------|------------|
| 基本概念 | `basic` |
| 线性结构 | `linear` |
| 树 | `tree` |
| 模拟 | `simulation` |
| 搜索 | `search` |
| 图 | `graph` |
| 数据结构 | `data-structure` |
| 算法 | `algorithm` |
| 数学 | `math` |
| 动态规划 | `dp` |
| 贪心 | `greedy` |
| 字符串 | `string` |

如需添加新的映射，请编辑 `src/services/api.ts` 中的 `knowledgePointMapping` 对象。

---

## 故障排除

### API 连接失败

**症状**: 控制台显示 `[StudentContext] API fetch failed`

**解决方案**:

1. 确认 Ascend API 服务已启动
2. 检查 `.env` 中的 `VITE_API_BASE` 配置
3. 确认 CORS 配置正确

**Ascend Django CORS 配置** (`settings.py`):

```python
CORS_ALLOWED_ORIGINS = [
    "http://localhost:5173",
    "http://localhost:3000",
]
```

### 降级模式

当 API 不可用时，系统自动进入降级模式：

- 所有标签显示默认亮度 (50%)
- 无雷电特效
- 无学习路径连接线
- 基本交互功能正常

### 标签位置不正确

如果学习路径连接线位置异常：

1. 确认 `CoreTags` 组件的 `onPositionsUpdate` 回调已正确传递
2. 检查 `tagPositions` Map 是否包含路径中的所有标签ID

### 特效不显示

1. 确认浏览器支持 SVG 滤镜
2. 检查 `SVGDefinitions` 组件是否正确渲染
3. 查看控制台是否有相关错误

---

## 文件结构

```
src/
├── services/
│   └── api.ts                 # API 服务层
├── contexts/
│   └── StudentContext.tsx     # 学生数据 Context
├── components/
│   └── KnowledgeGraph/
│       ├── PathConnectors.tsx # 路径连接线组件
│       ├── effects/
│       │   └── LightningEffect.tsx  # 雷电效果组件
│       ├── SVGDefinitions.tsx # SVG 滤镜定义（已扩展）
│       ├── CoreTags.tsx       # 核心标签（已扩展）
│       ├── types.ts           # 类型定义（已扩展）
│       └── ...
└── App.tsx                    # 应用入口（已集成 StudentProvider）
```

---

## 更新日志

### v1.0.0 (2025-01-25)

- 初始集成 Ascend API
- 实现掌握度亮度映射
- 实现薄弱知识点雷电特效
- 实现学习路径激光流连接线
- 添加降级策略支持
