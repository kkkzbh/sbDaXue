export module kompier.frontend.lex.lexer;

import std;

import kompier.basic.diagnostic;
import kompier.basic.source;
import kompier.frontend.lex.token;

export namespace kompier::frontend::lex {

/// 将源文本转换为一串词法单元。
///
/// 当前实现按字节处理，主要面向英文标识符；同时跟踪基础空白信息（行首 / 前导空白），
/// 为将来的布局/缩进敏感特性做准备。
class Lexer {
public:
    /// 为给定源文件创建词法分析器。
    ///
    /// 若诊断引擎非空，则词法错误会被记录到其中。
    explicit Lexer(const basic::SourceText& src, basic::DiagnosticEngine* diags = nullptr);

    /// 读取并返回下一个词法单元。
    auto next() -> Token;

private:
    const basic::SourceText* src_;
    std::string_view input_;
    basic::DiagnosticEngine* diags_;
    std::size_t pos_ = 0;
    bool at_line_start_ = true;

    /// 当前读指针位于文件末尾或越过文件末尾时返回真。
    auto eof() const -> bool { return pos_ >= input_.size(); }

    /// 查看当前位置字符（或前瞻若干个字符之后的字符）；到达文件末尾时返回 '\0'。
    auto peek(std::size_t lookahead = 0) const -> char;

    /// 将读指针前进指定字节数（会夹到文件末尾）。
    auto advance(std::size_t n = 1) -> void { pos_ = std::min(pos_ + n, input_.size()); }

    /// 跳过空白与注释，并更新空白信息标记。
    auto skip_trivia(bool& start_of_line, bool& leading_space) -> void;

    /// 解析标识符或关键字；调用方保证当前位置是合法起始字符。
    auto lex_identifier_or_keyword(bool start_of_line, bool leading_space) -> Token;

    /// 解析整数/浮点数字面量。
    ///
    /// 支持：常见进制前缀、数字分隔符、科学计数法指数部分、以及浮点/整数后缀。
    auto lex_number(bool start_of_line, bool leading_space) -> Token;

    /// 解析字符字面量（起始为单引号）。
    auto lex_char_literal(bool start_of_line, bool leading_space) -> Token;

    /// 解析字符串字面量（起始为双引号）。
    auto lex_string_literal(bool start_of_line, bool leading_space) -> Token;

    /// 生成一个词法单元对象。
    auto make_token(TokenKind kind, std::size_t begin, std::size_t end, bool start_of_line, bool leading_space) const
        -> Token;

    /// 若存在诊断引擎，则发出一条错误诊断。
    auto error(std::size_t begin, std::size_t end, std::string msg) -> void;
};

} // namespace kompier::frontend::lex

namespace kompier::frontend::lex {

/// 判断是否为英文字母（仅覆盖基本拉丁字母）。
static constexpr auto is_ascii_alpha(char c) -> bool
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/// 判断是否为数字字符（0-9）。
static constexpr auto is_ascii_digit(char c) -> bool
{
    return (c >= '0' && c <= '9');
}

/// 标识符起始字符判断。
static constexpr auto is_ident_start(char c) -> bool
{
    return is_ascii_alpha(c) || c == '_';
}

/// 标识符后续字符判断。
static constexpr auto is_ident_continue(char c) -> bool
{
    return is_ident_start(c) || is_ascii_digit(c);
}

/// 判断是否为十六进制数字字符。
static constexpr auto is_hex_digit(char c) -> bool
{
    return is_ascii_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

/// 判断是否为八进制数字字符。
static constexpr auto is_oct_digit(char c) -> bool
{
    return (c >= '0' && c <= '7');
}

/// 判断是否为二进制数字字符。
static constexpr auto is_bin_digit(char c) -> bool
{
    return c == '0' || c == '1';
}

/// 将关键字文本映射到对应的种类。
static auto keyword_kind(std::string_view s) -> std::optional<TokenKind>
{
    if (s == "module") {
        return TokenKind::KwModule;
    }
    if (s == "import") {
        return TokenKind::KwImport;
    }
    if (s == "export") {
        return TokenKind::KwExport;
    }
    if (s == "using") {
        return TokenKind::KwUsing;
    }
    if (s == "namespace") {
        return TokenKind::KwNamespace;
    }
    if (s == "as") {
        return TokenKind::KwAs;
    }
    if (s == "trait") {
        return TokenKind::KwTrait;
    }
    if (s == "impl") {
        return TokenKind::KwImpl;
    }
    if (s == "for") {
        return TokenKind::KwFor;
    }
    if (s == "sealed") {
        return TokenKind::KwSealed;
    }
    if (s == "const") {
        return TokenKind::KwConst;
    }
    if (s == "mut") {
        return TokenKind::KwMut;
    }
    if (s == "return") {
        return TokenKind::KwReturn;
    }
    if (s == "if") {
        return TokenKind::KwIf;
    }
    if (s == "else") {
        return TokenKind::KwElse;
    }
    if (s == "while") {
        return TokenKind::KwWhile;
    }
    if (s == "break") {
        return TokenKind::KwBreak;
    }
    if (s == "continue") {
        return TokenKind::KwContinue;
    }
    if (s == "void") {
        return TokenKind::KwVoid;
    }
    return std::nullopt;
}

Lexer::Lexer(const basic::SourceText& src, basic::DiagnosticEngine* diags)
    : src_(&src), input_(src.text()), diags_(diags)
{
}

auto Lexer::peek(std::size_t lookahead) const -> char
{
    const auto i = pos_ + lookahead;
    if (i >= input_.size()) {
        return '\0';
    }
    return input_[i];
}

auto Lexer::make_token(TokenKind kind, std::size_t begin, std::size_t end, bool start_of_line, bool leading_space) const
    -> Token
{
    return Token{.kind = kind, .span = basic::Span{begin, end}, .start_of_line = start_of_line, .leading_space = leading_space};
}

auto Lexer::error(std::size_t begin, std::size_t end, std::string msg) -> void
{
    if (diags_ == nullptr) {
        return;
    }
    diags_->error(basic::Span{begin, end}, std::move(msg));
}

auto Lexer::skip_trivia(bool& start_of_line, bool& leading_space) -> void
{
    while (!eof()) {
        const auto c = peek();

        // 水平空白。
        if (c == ' ' || c == '\t' || c == '\r') {
            leading_space = true;
            advance();
            continue;
        }

        // 换行会重置行首状态。
        if (c == '\n') {
            leading_space = true;
            start_of_line = true;
            at_line_start_ = true;
            advance();
            continue;
        }

        // 行注释：吞掉直到行末。
        if (c == '/' && peek(1) == '/') {
            leading_space = true;
            advance(2);
            while (!eof() && peek() != '\n') {
                advance();
            }
            continue;
        }

        // 块注释：吞到 */（或文件末尾）。
        if (c == '/' && peek(1) == '*') {
            leading_space = true;
            advance(2);
            bool closed = false;
            while (!eof()) {
                if (peek() == '\n') {
                    start_of_line = true;
                    at_line_start_ = true;
                    advance();
                    continue;
                }

                if (peek() == '*' && peek(1) == '/') {
                    advance(2);
                    closed = true;
                    break;
                }
                advance();
            }

            if (!closed) {
                error(pos_, pos_, "unterminated block comment");
            }
            continue;
        }

        break;
    }
}

auto Lexer::lex_identifier_or_keyword(bool start_of_line, bool leading_space) -> Token
{
    const auto begin = pos_;
    advance();
    while (!eof() && is_ident_continue(peek())) {
        advance();
    }

    const auto lexeme = input_.substr(begin, pos_ - begin);
    if (const auto kw = keyword_kind(lexeme)) {
        return make_token(*kw, begin, pos_, start_of_line, leading_space);
    }
    return make_token(TokenKind::Identifier, begin, pos_, start_of_line, leading_space);
}

auto Lexer::lex_number(bool start_of_line, bool leading_space) -> Token
{
    const auto begin = pos_;
    bool is_float = false;

    // 消费一串数字，允许在两个数字之间出现 '_' 与 '\'' 分隔符。
    // 返回值表示是否至少消费了一个数字。
    auto consume_digits = [&](auto is_digit) -> bool {
        bool any = false;
        bool last_was_digit = false;
        while (!eof()) {
            const auto c = peek();
            if (is_digit(c)) {
                any = true;
                last_was_digit = true;
                advance();
                continue;
            }

            // 分隔符只允许出现在两个数字之间。
            if ((c == '_' || c == '\'') && last_was_digit && is_digit(peek(1))) {
                last_was_digit = false;
                advance();
                continue;
            }
            break;
        }
        return any;
    };

    if (peek() == '.') {
        is_float = true;
        advance();
        if (!consume_digits(is_ascii_digit)) {
            error(begin, pos_, "expected digits after '.' in float literal");
        }
    } else if (peek() == '0' && (peek(1) == 'x' || peek(1) == 'X')) {
        advance(2);
        if (!consume_digits(is_hex_digit)) {
            error(begin, pos_, "expected hex digits after '0x'");
        }
    } else if (peek() == '0' && (peek(1) == 'b' || peek(1) == 'B')) {
        advance(2);
        if (!consume_digits(is_bin_digit)) {
            error(begin, pos_, "expected binary digits after '0b'");
        }
    } else if (peek() == '0' && (peek(1) == 'o' || peek(1) == 'O')) {
        advance(2);
        if (!consume_digits(is_oct_digit)) {
            error(begin, pos_, "expected octal digits after '0o'");
        }
    } else {
        consume_digits(is_ascii_digit);

        if (peek() == '.') {
            is_float = true;
            advance();
            consume_digits(is_ascii_digit);
        }

        if (peek() == 'e' || peek() == 'E') {
            is_float = true;
            advance();
            if (peek() == '+' || peek() == '-') {
                advance();
            }
            if (!consume_digits(is_ascii_digit)) {
                error(begin, pos_, "expected digits in exponent part");
            }
        }
    }

    if (is_float) {
        // 可选浮点后缀。
        if (peek() == 'f' || peek() == 'F') {
            advance();
        }
        return make_token(TokenKind::FloatLiteral, begin, pos_, start_of_line, leading_space);
    }

    // 整数后缀：无符号与长整型标记，顺序不限且每种最多出现一次。
    bool seen_u = false;
    bool seen_l = false;
    while (true) {
        const auto c = peek();
        if ((c == 'u' || c == 'U') && !seen_u) {
            seen_u = true;
            advance();
            continue;
        }
        if ((c == 'l' || c == 'L') && !seen_l) {
            seen_l = true;
            advance();
            continue;
        }
        break;
    }

    return make_token(TokenKind::IntLiteral, begin, pos_, start_of_line, leading_space);
}

auto Lexer::lex_char_literal(bool start_of_line, bool leading_space) -> Token
{
    const auto begin = pos_;
    advance(); // '

    // 错误恢复：吞到换行或遇到闭合引号（若存在）。
    auto unterminated = [&] {
        error(begin, pos_, "unterminated character literal");
        while (!eof() && peek() != '\n' && peek() != '\'') {
            advance();
        }
        if (peek() == '\'') {
            advance();
        }
        return make_token(TokenKind::Invalid, begin, pos_, start_of_line, leading_space);
    };

    if (eof() || peek() == '\n') {
        return unterminated();
    }

    if (peek() == '\\') {
        advance();
        const auto esc = peek();
        if (esc == '\0') {
            return unterminated();
        }
        advance();

        // 最小化支持十六进制转义。
        if (esc == 'x') {
            if (!is_hex_digit(peek()) || !is_hex_digit(peek(1))) {
                error(begin, pos_, "expected two hex digits after '\\x'");
            }
            if (is_hex_digit(peek())) {
                advance();
            }
            if (is_hex_digit(peek())) {
                advance();
            }
        }
    } else {
        advance();
    }

    if (peek() != '\'') {
        return unterminated();
    }
    advance();
    return make_token(TokenKind::CharLiteral, begin, pos_, start_of_line, leading_space);
}

auto Lexer::lex_string_literal(bool start_of_line, bool leading_space) -> Token
{
    const auto begin = pos_;
    advance(); // "

    while (!eof()) {
        const auto c = peek();
        if (c == '"') {
            advance();
            return make_token(TokenKind::StringLiteral, begin, pos_, start_of_line, leading_space);
        }

        // 普通字符串字面量不允许出现换行。
        if (c == '\n') {
            error(begin, pos_, "unterminated string literal");
            return make_token(TokenKind::Invalid, begin, pos_, start_of_line, leading_space);
        }

        if (c == '\\') {
            advance();
            const auto esc = peek();
            if (esc == '\0') {
                break;
            }
            advance();

            // 最小化支持十六进制转义。
            if (esc == 'x') {
                if (!is_hex_digit(peek()) || !is_hex_digit(peek(1))) {
                    error(begin, pos_, "expected two hex digits after '\\x'");
                }
                if (is_hex_digit(peek())) {
                    advance();
                }
                if (is_hex_digit(peek())) {
                    advance();
                }
            }
            continue;
        }

        advance();
    }

    error(begin, pos_, "unterminated string literal");
    return make_token(TokenKind::Invalid, begin, pos_, start_of_line, leading_space);
}

auto Lexer::next() -> Token
{
    bool leading_space = false;
    bool start_of_line = at_line_start_;
    skip_trivia(start_of_line, leading_space);

    if (eof()) {
        return make_token(TokenKind::Eof, pos_, pos_, start_of_line, leading_space);
    }

    const auto c = peek();

    auto tok = Token{};
    if (is_ident_start(c)) {
        tok = lex_identifier_or_keyword(start_of_line, leading_space);
    } else if (is_ascii_digit(c) || (c == '.' && is_ascii_digit(peek(1)))) {
        tok = lex_number(start_of_line, leading_space);
    } else if (c == '\'') {
        tok = lex_char_literal(start_of_line, leading_space);
    } else if (c == '"') {
        tok = lex_string_literal(start_of_line, leading_space);
    } else if (c == ':' && peek(1) == ':') {
        const auto begin = pos_;
        advance(2);
        tok = make_token(TokenKind::ColonColon, begin, pos_, start_of_line, leading_space);
    } else if (c == '-' && peek(1) == '>') {
        const auto begin = pos_;
        advance(2);
        tok = make_token(TokenKind::Arrow, begin, pos_, start_of_line, leading_space);
    } else {
        // 单字符词法单元以及非法字符。
        const auto begin = pos_;
        advance();
        const auto kind = [&] {
            switch (c) {
            case '(':
                return TokenKind::LParen;
            case ')':
                return TokenKind::RParen;
            case '{':
                return TokenKind::LBrace;
            case '}':
                return TokenKind::RBrace;
            case '[':
                return TokenKind::LBracket;
            case ']':
                return TokenKind::RBracket;
            case ',':
                return TokenKind::Comma;
            case ';':
                return TokenKind::Semicolon;
            case ':':
                return TokenKind::Colon;
            case '.':
                return TokenKind::Dot;
            case '<':
                return TokenKind::Less;
            case '>':
                return TokenKind::Greater;
            case '=':
                return TokenKind::Equal;
            case '+':
                return TokenKind::Plus;
            case '-':
                return TokenKind::Minus;
            case '*':
                return TokenKind::Star;
            case '/':
                return TokenKind::Slash;
            default:
                return TokenKind::Invalid;
            }
        }();

        if (kind == TokenKind::Invalid) {
            error(begin, pos_, std::string("unexpected character '") + c + "'");
        }

        tok = make_token(kind, begin, pos_, start_of_line, leading_space);
    }

    at_line_start_ = false;
    return tok;
}

} // namespace kompier::frontend::lex
