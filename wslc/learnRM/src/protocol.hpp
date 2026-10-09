#pragma once

// 文本协议解析与格式化模块
// 协议设计简洁，适合 nc 客户端使用

#include <string>
#include <string_view>
#include <optional>
#include <variant>
#include <chrono>
#include <format>
#include <charconv>

namespace chat::protocol {

// ============================================================================
// 客户端命令类型
// ============================================================================

struct JoinCmd {
    std::string name;
};

struct MsgCmd {
    std::string content;
};

struct QuitCmd {};

struct InvalidCmd {
    std::string reason;
};

using Command = std::variant<JoinCmd, MsgCmd, QuitCmd, InvalidCmd>;

// ============================================================================
// 协议解析器
// ============================================================================

class Parser {
public:
    // 解析一行客户端输入
    [[nodiscard]] static Command parse(std::string_view line) {
        // 移除末尾的 \r\n 或 \n
        line = trim_crlf(line);
        
        if (line.empty()) {
            return InvalidCmd{"Empty command"};
        }

        // 分割命令和参数
        auto space_pos = line.find(' ');
        std::string_view cmd = (space_pos != std::string_view::npos) 
            ? line.substr(0, space_pos) 
            : line;
        std::string_view args = (space_pos != std::string_view::npos) 
            ? line.substr(space_pos + 1) 
            : std::string_view{};

        // 命令匹配 (大小写不敏感)
        if (iequals(cmd, "JOIN")) {
            if (args.empty()) {
                return InvalidCmd{"JOIN requires a name"};
            }
            // 名字不能包含空格，取第一个词
            auto name_end = args.find(' ');
            std::string name{args.substr(0, name_end)};
            if (name.length() > 64) {
                return InvalidCmd{"Name too long (max 64 chars)"};
            }
            return JoinCmd{std::move(name)};
        }
        
        if (iequals(cmd, "MSG")) {
            if (args.empty()) {
                return InvalidCmd{"MSG requires content"};
            }
            return MsgCmd{std::string{args}};
        }
        
        if (iequals(cmd, "QUIT")) {
            return QuitCmd{};
        }

        return InvalidCmd{std::format("Unknown command: {}", cmd)};
    }

private:
    static std::string_view trim_crlf(std::string_view sv) {
        while (!sv.empty() && (sv.back() == '\r' || sv.back() == '\n')) {
            sv.remove_suffix(1);
        }
        return sv;
    }

    static bool iequals(std::string_view a, std::string_view b) {
        if (a.size() != b.size()) return false;
        for (std::size_t i = 0; i < a.size(); ++i) {
            if (std::tolower(static_cast<unsigned char>(a[i])) != 
                std::tolower(static_cast<unsigned char>(b[i]))) {
                return false;
            }
        }
        return true;
    }
};

// ============================================================================
// 响应格式化器
// ============================================================================

class Formatter {
public:
    // OK JOINED <name>
    [[nodiscard]] static std::string ok_joined(std::string_view name) {
        return std::format("OK JOINED {}\n", name);
    }

    // OK QUIT
    [[nodiscard]] static std::string ok_quit() {
        return "OK QUIT\n";
    }

    // HISTORY <n>
    [[nodiscard]] static std::string history_start(std::size_t count) {
        return std::format("HISTORY {}\n", count);
    }

    // MSG <sender> <timestamp> <content>
    [[nodiscard]] static std::string msg(
        std::string_view sender, 
        std::string_view timestamp,
        std::string_view content
    ) {
        return std::format("MSG {} {} {}\n", sender, timestamp, content);
    }

    // MSG with current time
    [[nodiscard]] static std::string msg(
        std::string_view sender,
        std::string_view content
    ) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        localtime_r(&time_t, &tm_buf);
        char time_str[20];
        std::strftime(time_str, sizeof(time_str), "%H:%M:%S", &tm_buf);
        return msg(sender, time_str, content);
    }

    // ERR <code> <message>
    [[nodiscard]] static std::string err(int code, std::string_view message) {
        return std::format("ERR {} {}\n", code, message);
    }

    // SYS <message>
    [[nodiscard]] static std::string sys(std::string_view message) {
        return std::format("SYS {}\n", message);
    }

    // 用户加入系统消息
    [[nodiscard]] static std::string sys_joined(std::string_view name) {
        return sys(std::format("{} joined", name));
    }

    // 用户离开系统消息
    [[nodiscard]] static std::string sys_left(std::string_view name) {
        return sys(std::format("{} left", name));
    }
};

// ============================================================================
// 消息结构 (用于内部传递和缓存)
// ============================================================================

struct ChatMessage {
    std::string sender;
    std::string content;
    std::string timestamp;

    // 序列化为 Redis 存储格式: sender|timestamp|content
    [[nodiscard]] std::string serialize() const {
        return std::format("{}|{}|{}", sender, timestamp, content);
    }

    // 从 Redis 格式反序列化
    [[nodiscard]] static std::optional<ChatMessage> deserialize(std::string_view data) {
        auto pos1 = data.find('|');
        if (pos1 == std::string_view::npos) return std::nullopt;
        
        auto pos2 = data.find('|', pos1 + 1);
        if (pos2 == std::string_view::npos) return std::nullopt;

        return ChatMessage{
            .sender = std::string{data.substr(0, pos1)},
            .content = std::string{data.substr(pos2 + 1)},
            .timestamp = std::string{data.substr(pos1 + 1, pos2 - pos1 - 1)}
        };
    }

    // 格式化为协议消息
    [[nodiscard]] std::string format() const {
        return Formatter::msg(sender, timestamp, content);
    }
};

}  // namespace chat::protocol
