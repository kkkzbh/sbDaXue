export module kompier.basic.diagnostic;

import std;

import kompier.basic.source;

export namespace kompier::basic {

/// 诊断级别（严重程度）。
enum class DiagnosticLevel {
    Note,
    Warning,
    Error,
};

/// 一条诊断信息，关联到某段源代码区间。
struct Diagnostic {
    DiagnosticLevel level{};
    Span span{};
    std::string message;
};

/// 收集诊断并以带源码上下文的形式打印。
class DiagnosticEngine {
public:
    /// 添加提示。
    auto note(Span sp, std::string msg) -> void { diags_.push_back({DiagnosticLevel::Note, sp, std::move(msg)}); }
    /// 添加警告。
    auto warning(Span sp, std::string msg) -> void { diags_.push_back({DiagnosticLevel::Warning, sp, std::move(msg)}); }
    /// 添加错误。
    auto error(Span sp, std::string msg) -> void { diags_.push_back({DiagnosticLevel::Error, sp, std::move(msg)}); }

    /// 若存在错误级别诊断则返回真值。
    auto has_errors() const -> bool;

    /// 以常见编译器诊断的格式将所有诊断打印到输出流。
    ///
    /// 输出包含：诊断所在行文本 + 插入符/范围 标记。
    auto print(std::ostream& out, const SourceText& src) const -> void;

private:
    std::vector<Diagnostic> diags_;
};

} // namespace kompier::basic

namespace kompier::basic {

/// 返回诊断级别的可读名称。
static auto level_name(DiagnosticLevel level) -> std::string_view
{
    switch (level) {
    case DiagnosticLevel::Note:
        return "note";
    case DiagnosticLevel::Warning:
        return "warning";
    case DiagnosticLevel::Error:
        return "error";
    }
    return "error";
}

auto DiagnosticEngine::has_errors() const -> bool
{
    return std::ranges::any_of(diags_, [](const Diagnostic& d) { return d.level == DiagnosticLevel::Error; });
}

auto DiagnosticEngine::print(std::ostream& out, const SourceText& src) const -> void
{
    for (const auto& d : diags_) {
        const auto loc = src.line_map().locate(d.span.begin);
        std::println(out, "{}:{}:{}: {}: {}", src.path(), loc.line, loc.column, level_name(d.level), d.message);

        const auto line_text = src.line_text_at(d.span.begin);
        std::println(out, "  {}", line_text);

        // 插入符（^）指向区间的起始位置。
        const auto caret_col = std::max<std::uint32_t>(1, loc.column);
        std::print(out, "  {}^", std::string(static_cast<std::size_t>(caret_col - 1), ' '));

        // 如果区间覆盖多个字节，则用 '~' 延展以提示范围。
        const auto len = d.span.size();
        if (len > 1) {
            std::print(out, "{}", std::string(static_cast<std::size_t>(len - 1), '~'));
        }
        std::print(out, "\n");
    }
}

} // namespace kompier::basic
