#!/bin/bash

# 刺杀博弈游戏 - 启动脚本
# 同时启动前端和后端服务

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

BACKEND_PORT=21447

echo -e "${GREEN}🎯 刺杀博弈游戏 - 启动中...${NC}"
echo ""

# 检查 Python
if ! command -v python3 &> /dev/null; then
    echo -e "${RED}❌ 未找到 Python3，请先安装 Python${NC}"
    exit 1
fi

# 检查 Node.js
if ! command -v node &> /dev/null; then
    echo -e "${RED}❌ 未找到 Node.js，请先安装 Node.js${NC}"
    exit 1
fi

# 检查 npm
if ! command -v npm &> /dev/null; then
    echo -e "${RED}❌ 未找到 npm，请先安装 npm${NC}"
    exit 1
fi

# 安装后端依赖
echo -e "${YELLOW}📦 检查后端依赖...${NC}"
python3 -c "import fastapi, uvicorn, pydantic" 2>/dev/null || {
    echo -e "${YELLOW}正在安装后端依赖...${NC}"
    PIP_ARGS=()
    if [ -z "${VIRTUAL_ENV:-}" ]; then
        PIP_ARGS+=(--user)
    fi
    python3 -m pip install "${PIP_ARGS[@]}" -r backend/requirements.txt
}

# 安装前端依赖
echo -e "${YELLOW}📦 检查前端依赖...${NC}"
cd frontend
if [ ! -d "node_modules" ]; then
    echo -e "${YELLOW}正在安装前端依赖...${NC}"
    npm install
fi
cd ..

# 启动后端
echo -e "${GREEN}🚀 启动后端服务 (端口 ${BACKEND_PORT})...${NC}"
cd backend
python3 -m uvicorn main:app --reload --host 0.0.0.0 --port "${BACKEND_PORT}" &
BACKEND_PID=$!
cd ..

# 等待后端启动
sleep 2

# 启动前端
echo -e "${GREEN}🚀 启动前端服务 (端口 5173)...${NC}"
cd frontend
npm run dev &
FRONTEND_PID=$!
cd ..

# 打印信息
echo ""
echo -e "${GREEN}✅ 服务已启动!${NC}"
echo ""
echo -e "  🔧 后端 API:   ${YELLOW}http://localhost:${BACKEND_PORT}${NC}"
echo -e "  📖 API 文档:   ${YELLOW}http://localhost:${BACKEND_PORT}/docs${NC}"
echo -e "  🎮 前端界面:   ${YELLOW}http://localhost:5173${NC}"
echo ""
echo -e "${YELLOW}按 Ctrl+C 停止所有服务${NC}"

# 等待并处理退出
cleanup() {
    if [ -n "${BACKEND_PID:-}" ]; then
        kill "$BACKEND_PID" 2>/dev/null || true
    fi
    if [ -n "${FRONTEND_PID:-}" ]; then
        kill "$FRONTEND_PID" 2>/dev/null || true
    fi
    echo -e "\n${GREEN}👋 服务已停止${NC}"
}
trap cleanup EXIT
wait
