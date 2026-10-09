# spec

这些文件尝试把 `design/*.kk` 里的想法整理成“可以直接写编译器”的最小规格（v0）。

全局约定（按你在对话里确认的版本）：
- 任何没写出来的类型都需要推导；推导不了（或推导功能尚未实现）= 编译报错：无法推导
- 读取未初始化值 = 编译错误（definite assignment analysis）

目录（建议阅读顺序）：
- `design/spec/lexical.md`：词法（token）草案
- `design/spec/grammar.md`：语法骨架（EBNF 草案）
- `design/spec/scopes-and-decls.md`：作用域/名字解析/声明规则（含“首次赋值即声明”）
- `design/spec/types-and-inference.md`：类型系统与推导（v0）
- `design/spec/definite-assignment.md`：未初始化值规则（v0）
- `design/spec/generics-and-constraints.md`：泛型与约束（v0）
- `design/spec/traits-and-interfaces.md`：trait/interface 全面解释（面向 C++ 思维）
- `design/spec/modules.md`：模块系统（import/export、可见性）

状态：这些是“能落地实现”的默认建议，你可以随时改；改动时尽量同步 `design/*.kk` 示例。
