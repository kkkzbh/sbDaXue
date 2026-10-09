import std;

import kompier.basic.diagnostic;
import kompier.basic.source;
import kompier.frontend.lex.lexer;
import kompier.frontend.lex.token;

namespace {

using kompier::basic::DiagnosticEngine;
using kompier::basic::load_source_text;
using kompier::frontend::lex::Lexer;
using kompier::frontend::lex::TokenKind;
using kompier::frontend::lex::token_kind_name;

/// 打印命令行用法到标准错误。
auto print_usage() -> void
{
    std::println(std::cerr, "usage:");
    std::println(std::cerr, "  kk lex <file>");
}

/// 运行词法分析子命令。
///
/// 加载源文件、进行词法分析，并将词法单元逐行输出到标准输出。
auto cmd_lex(std::string_view path) -> int
{
    std::string err;
    auto src_opt = load_source_text(path, err);
    if (!src_opt) {
        std::println(std::cerr, "error: {}", err);
        return 1;
    }

    const auto& src = *src_opt;
    auto diags = DiagnosticEngine{};
    auto lexer = Lexer{src, &diags};

    // 以稳定格式输出词法单元，便于黄金用例比对。
    for (;;) {
        const auto tok = lexer.next();
        const auto loc = src.line_map().locate(tok.span.begin);
        const auto lexeme = src.slice(tok.span);

        if (tok.kind == TokenKind::Eof) {
            std::println(std::cout, "{}:{} {} <eof>", loc.line, loc.column, token_kind_name(tok.kind));
        } else {
            std::println(std::cout, "{}:{} {} {}", loc.line, loc.column, token_kind_name(tok.kind), lexeme);
        }

        if (tok.kind == TokenKind::Eof) {
            break;
        }
    }

    if (diags.has_errors()) {
        diags.print(std::cerr, src);
        return 1;
    }

    return 0;
}

} // namespace

/// 命令行入口。
auto main(int argc, char** argv) -> int
{
    // 为了更快的输入输出：关闭与标准库低层输入输出的同步，并解除输入流绑定。
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto args = std::span(argv, static_cast<std::size_t>(argc));
    if (args.size() < 2) {
        print_usage();
        return 1;
    }

    const auto cmd = std::string_view(args[1]);
    if (cmd == "lex") {
        if (args.size() != 3) {
            print_usage();
            return 1;
        }
        return cmd_lex(args[2]);
    }

    std::println(std::cerr, "error: unknown command: {}", cmd);
    print_usage();
    return 1;
}
