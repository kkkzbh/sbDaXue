-- 聊天消息表
CREATE TABLE IF NOT EXISTS messages (
    id BIGSERIAL PRIMARY KEY,
    sender VARCHAR(64) NOT NULL,
    content TEXT NOT NULL,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

-- 按时间倒序索引，用于查询最近消息
CREATE INDEX IF NOT EXISTS idx_messages_created_at ON messages(created_at DESC);

-- 可选：分区表（生产环境按月分区）
-- 学习项目暂不使用
