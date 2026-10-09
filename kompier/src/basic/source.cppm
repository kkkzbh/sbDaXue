export module kompier.basic.source;

import std;

export namespace kompier::basic {

using Offset = std::size_t;

/// 源代码的半开区间（按字节偏移计）：[起始, 结束)。
struct Span {
    Offset begin{};
    Offset end{};

    /// 返回该区间覆盖的字节数。
    constexpr auto size() const -> Offset { return end - begin; }
    /// 起始偏移等于结束偏移时返回真。
    constexpr auto empty() const -> bool { return begin == end; }
};

/// 行/列位置（从 1 开始计数）。
struct Location {
    std::uint32_t line{};
    std::uint32_t column{};
};

/// 将字节偏移映射为（行, 列）（从 1 开始计数）。
///
/// 行以换行符分割；列按字节计数（不是按字符计数）。
class LineMap {
public:
    LineMap() = default;

    /// 为给定源文本构建行映射表。
    explicit LineMap(std::string_view text);

    /// 将绝对字节偏移转换为（行, 列）（从 1 开始计数）。
    auto locate(Offset offset) const -> Location;

    /// 返回某个行号对应的 [起始, 结束) 边界（行号从 1 开始计数）。
    ///
    /// 结束位置是下一行的起始位置（或文件末尾），因此可能包含行尾的换行符。
    auto line_bounds(std::uint32_t line) const -> std::pair<Offset, Offset>;

private:
    Offset size_ = 0;
    std::vector<Offset> line_starts_{0};
};

/// 已加载到内存的源文件（包含路径与预计算的行映射）。
class SourceText {
public:
    SourceText() = default;

    /// 构造源缓冲区并建立行映射。
    SourceText(std::string path, std::string text);

    /// 返回源文件路径（加载时提供的字符串）。
    auto path() const -> std::string_view { return path_; }
    /// 返回完整源文本。
    auto text() const -> std::string_view { return text_; }
    /// 返回由源文本构建的行映射。
    auto line_map() const -> const LineMap& { return line_map_; }

    /// 返回给定区间对应的源文本视图。
    ///
    /// 索引会被夹到合法范围；若结束偏移小于起始偏移，则结果为空。
    auto slice(Span sp) const -> std::string_view;

    /// 返回包含给定字节偏移的那一行的文本。
    ///
    /// 返回的视图会去掉行尾终止符（换行符与回车符）。
    auto line_text_at(Offset offset) const -> std::string_view;

private:
    std::string path_;
    std::string text_;
    LineMap line_map_;
};

/// 将文件加载到内存。
///
/// 失败时返回空，并将可读错误信息写入错误信息字符串。
auto load_source_text(std::string_view path, std::string& error) -> std::optional<SourceText>;

} // namespace kompier::basic

namespace kompier::basic {

LineMap::LineMap(std::string_view text) : size_(text.size())
{
    line_starts_.clear();
    line_starts_.push_back(0);

    // 记录每一行的起始字节位置。
    for (Offset i = 0; i < text.size(); ++i) {
        if (text[i] == '\n') {
            line_starts_.push_back(i + 1);
        }
    }
}

auto LineMap::locate(Offset offset) const -> Location
{
    const auto clamped = std::min(offset, size_);

    // 用二分查找定位给定偏移所在行的起始位置。
    const auto it = std::upper_bound(line_starts_.begin(), line_starts_.end(), clamped);
    const auto idx = (it == line_starts_.begin()) ? std::size_t{0}
                                                   : static_cast<std::size_t>(it - line_starts_.begin() - 1);

    const auto line_start = line_starts_[idx];
    return Location{static_cast<std::uint32_t>(idx + 1),
                    static_cast<std::uint32_t>(clamped - line_start + 1)};
}

auto LineMap::line_bounds(std::uint32_t line) const -> std::pair<Offset, Offset>
{
    if (line < 1) {
        return {0, 0};
    }

    const auto idx = static_cast<std::size_t>(line - 1);
    if (idx >= line_starts_.size()) {
        return {size_, size_};
    }

    const auto start = line_starts_[idx];
    const auto end = (idx + 1 < line_starts_.size()) ? line_starts_[idx + 1] : size_;
    return {start, end};
}

SourceText::SourceText(std::string path, std::string text)
    : path_(std::move(path)),
      text_(std::move(text)),
      line_map_(std::string_view{text_})
{
}

auto SourceText::slice(Span sp) const -> std::string_view
{
    const auto n = text_.size();
    auto b = std::min(sp.begin, n);
    auto e = std::min(sp.end, n);
    if (e < b) {
        e = b;
    }
    return std::string_view{text_}.substr(b, e - b);
}

auto SourceText::line_text_at(Offset offset) const -> std::string_view
{
    const auto loc = line_map_.locate(offset);
    auto [start, end] = line_map_.line_bounds(loc.line);

    // 从返回视图中裁掉常见行终止符。
    while (end > start && (text_[end - 1] == '\n' || text_[end - 1] == '\r')) {
        --end;
    }

    return std::string_view{text_}.substr(start, end - start);
}

auto load_source_text(std::string_view path, std::string& error) -> std::optional<SourceText>
{
    error.clear();

    std::error_code ec;
    const auto size_umax = std::filesystem::file_size(std::filesystem::path{path}, ec);
    if (ec) {
        error = "cannot stat file: " + std::string(path);
        return std::nullopt;
    }

    if (size_umax > static_cast<std::uintmax_t>(std::numeric_limits<std::size_t>::max())) {
        error = "file too large: " + std::string(path);
        return std::nullopt;
    }

    const auto size = static_cast<std::size_t>(size_umax);

    // 使用标准库的低层文件读取接口以获得可预测、分配友好的读取路径。
    auto file = std::unique_ptr<std::FILE, int (*)(std::FILE*)>(std::fopen(std::string(path).c_str(), "rb"), &std::fclose);
    if (!file) {
        error = "cannot open file: " + std::string(path);
        return std::nullopt;
    }

    std::string data;
    data.resize(size);
    if (!data.empty()) {
        const auto n = std::fread(data.data(), 1, data.size(), file.get());
        if (n != data.size()) {
            error = "failed to read file: " + std::string(path);
            return std::nullopt;
        }
    }

    return SourceText{std::string(path), std::move(data)};
}

} // namespace kompier::basic
