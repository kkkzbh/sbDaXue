export module kompier.frontend.lex.token;

import std;

import kompier.basic.source;

export namespace kompier::frontend::lex {

/// 词法分析器产生的词法单元种类。
enum class TokenKind {
    Eof,
    Invalid,

    Identifier,
    IntLiteral,
    FloatLiteral,
    CharLiteral,
    StringLiteral,

    KwModule,
    KwImport,
    KwExport,
    KwUsing,
    KwNamespace,
    KwAs,
    KwTrait,
    KwImpl,
    KwFor,
    KwSealed,
    KwConst,
    KwMut,
    KwReturn,
    KwIf,
    KwElse,
    KwWhile,
    KwBreak,
    KwContinue,
    KwVoid,

    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,
    Comma,
    Semicolon,
    Colon,
    Dot,
    ColonColon,
    Arrow,
    Less,
    Greater,
    Equal,
    Plus,
    Minus,
    Star,
    Slash,
};

/// 单个词法单元：包含种类、源代码区间以及空白信息标记。
struct Token {
    TokenKind kind{};
    basic::Span span{};
    bool start_of_line = false;
    bool leading_space = false;
};

/// 返回稳定的可读名称（用于测试与调试输出）。
auto token_kind_name(TokenKind k) -> std::string_view;

} // namespace kompier::frontend::lex

namespace kompier::frontend::lex {

/// 返回稳定的词法单元名称字符串。
auto token_kind_name(TokenKind k) -> std::string_view
{
    switch (k) {
    case TokenKind::Eof:
        return "eof";
    case TokenKind::Invalid:
        return "invalid";
    case TokenKind::Identifier:
        return "identifier";
    case TokenKind::IntLiteral:
        return "int_lit";
    case TokenKind::FloatLiteral:
        return "float_lit";
    case TokenKind::CharLiteral:
        return "char_lit";
    case TokenKind::StringLiteral:
        return "string_lit";
    case TokenKind::KwModule:
        return "kw_module";
    case TokenKind::KwImport:
        return "kw_import";
    case TokenKind::KwExport:
        return "kw_export";
    case TokenKind::KwUsing:
        return "kw_using";
    case TokenKind::KwNamespace:
        return "kw_namespace";
    case TokenKind::KwAs:
        return "kw_as";
    case TokenKind::KwTrait:
        return "kw_trait";
    case TokenKind::KwImpl:
        return "kw_impl";
    case TokenKind::KwFor:
        return "kw_for";
    case TokenKind::KwSealed:
        return "kw_sealed";
    case TokenKind::KwConst:
        return "kw_const";
    case TokenKind::KwMut:
        return "kw_mut";
    case TokenKind::KwReturn:
        return "kw_return";
    case TokenKind::KwIf:
        return "kw_if";
    case TokenKind::KwElse:
        return "kw_else";
    case TokenKind::KwWhile:
        return "kw_while";
    case TokenKind::KwBreak:
        return "kw_break";
    case TokenKind::KwContinue:
        return "kw_continue";
    case TokenKind::KwVoid:
        return "kw_void";
    case TokenKind::LParen:
        return "l_paren";
    case TokenKind::RParen:
        return "r_paren";
    case TokenKind::LBrace:
        return "l_brace";
    case TokenKind::RBrace:
        return "r_brace";
    case TokenKind::LBracket:
        return "l_bracket";
    case TokenKind::RBracket:
        return "r_bracket";
    case TokenKind::Comma:
        return "comma";
    case TokenKind::Semicolon:
        return "semicolon";
    case TokenKind::Colon:
        return "colon";
    case TokenKind::Dot:
        return "dot";
    case TokenKind::ColonColon:
        return "colon_colon";
    case TokenKind::Arrow:
        return "arrow";
    case TokenKind::Less:
        return "less";
    case TokenKind::Greater:
        return "greater";
    case TokenKind::Equal:
        return "equal";
    case TokenKind::Plus:
        return "plus";
    case TokenKind::Minus:
        return "minus";
    case TokenKind::Star:
        return "star";
    case TokenKind::Slash:
        return "slash";
    }
    return "invalid";
}

} // namespace kompier::frontend::lex
