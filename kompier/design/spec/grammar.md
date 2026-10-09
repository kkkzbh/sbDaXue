# 语法骨架（EBNF，v0 草案）

这是“能写 parser 的最小骨架”，不是最终语法。

## 顶层

```ebnf
CompilationUnit  ::= ModuleDecl? TopItem*

TopItem          ::= ImportDecl
                 |  UsingStmt
                 |  TopLevelDecl

ModuleDecl       ::= 'export'? 'module' ModulePath ';'
ModulePath       ::= Identifier ('.' Identifier)*

ImportDecl       ::= 'export'? 'import' ModulePath ImportAliasOpt ';'

ImportAliasOpt   ::= ('as' Identifier)?

UsingStmt        ::= 'using' 'namespace' QualifiedName ';'
                 |  'using' QualifiedName UsingAliasOpt ';'

UsingAliasOpt    ::= ('as' Identifier)?

QualifiedName    ::= Identifier ('::' Identifier)*

// 注：QualifiedName 用于名字空间/模块路径访问，例如 `X::Y::Z::add`。
// `export module X.Y;` / `import X.Y;` 仍使用 `.` 书写模块路径。

TopLevelDecl     ::= FunctionDecl
                 |  TraitDecl
                 |  ImplDecl
                 |  /* future: const/type/global var decl */
```

## 函数

```ebnf
FunctionDecl     ::= ExportOpt Identifier GenericParamListOpt '(' ParamListOpt ')'
                     ReturnTypeOpt Block

ExportOpt        ::= 'export'?

GenericParamListOpt ::= GenericParamList?
GenericParamList ::= '<' GenericParam (',' GenericParam)* '>'
GenericParam     ::= Identifier (':' Constraint)?

Constraint       ::= Identifier // v0: 单个 trait 约束（例如 `U: Integer`）

ParamListOpt     ::= ParamList?
ParamList        ::= Param (',' Param)*
Param            ::= Identifier (':' Type)?

ReturnTypeOpt    ::= ('->' Type)?

Block            ::= '{' Stmt* '}'

TraitDecl        ::= ExportOpt SealedOpt 'trait' Identifier ';' // v0: marker trait
SealedOpt        ::= 'sealed'?
ImplDecl         ::= 'impl' Identifier 'for' Type ';'
```

说明：
- 你目前的示例是“函数没有 `fn` 关键字”，这里按示例保留。
- 参数/返回值没写类型都走推导；推导不了 = 报错（见 `design/spec/types-and-inference.md`）。

## 语句（最小）

```ebnf
Stmt             ::= VarDeclStmt ';'
                 |  AssignStmt ';'
                 |  ReturnStmt ';'
                 |  ExprStmt ';'
                 |  Block

VarDeclStmt      ::= 'const' Identifier '=' Expr
                 |  'mut'   Identifier '=' Expr

// 也允许“默认不可变”的绑定：
// - 若 `name` 未声明过，则 `name = expr;` 在语义上引入一个新变量（首次赋值即声明）
// - 若 `name` 已存在，则是对既有变量的赋值
// 语法上仍然是 `AssignStmt`（见 `design/spec/scopes-and-decls.md`）

// 注：没有 `x: T = ...` 的语法。任何变量绑定都必须带初始化表达式。
// 需要“未初始化值”时，用 `T{}` / `Type{}` / `[T; N]{}` / `(T1, T2){}` 等表达式。
// 另外：`AssignStmt` 在名字解析阶段可能被解释为“首次赋值即声明”（见 `design/spec/scopes-and-decls.md`）。

AssignStmt       ::= LValue '=' Expr
LValue           ::= Identifier
                 |  Expr '.' Identifier
                 |  Expr '[' Expr ']'

ReturnStmt       ::= 'return' Expr?
ExprStmt         ::= Expr
```

注：
- `AssignStmt` 的语义包含“首次赋值即声明”（见 `design/spec/scopes-and-decls.md`）。

## 表达式（占位骨架）

```ebnf
// 表达式优先级：采用 C++ 的表达式优先级与结合性。
// 实现建议：Pratt parser / precedence climbing。
// v0 语法里先只列出最常用的一小部分运算符（postfix/call/index/member，`*` `/`，`+` `-`）。

// 注：v0 里 `=` 是语句级别的赋值（`AssignStmt`），不是表达式运算符。
// 后续如果你想做成 C++ 一样“赋值是表达式”，再把 `=` 纳入表达式优先级表。

Expr             ::= AddExpr

AddExpr          ::= MulExpr (('+' | '-') MulExpr)*
MulExpr          ::= PostfixExpr (('*' | '/') PostfixExpr)*

PostfixExpr      ::= PrimaryExpr PostfixOp*
PostfixOp        ::= '(' ArgListOpt ')'
                 |  '[' Expr ']'
                 |  '.' Identifier

PrimaryExpr      ::= Literal
                  |  Identifier
                  |  QualifiedName
                  |  GroupExpr
                  |  TupleLiteral
                  |  ArrayLiteral
                  |  TypedInitExpr
                  |  ArrayCtorExpr
                  |  TupleCtorExpr

GroupExpr        ::= '(' Expr ')'

// TupleLiteral 至少包含一个逗号：
// - `(a, b)` 为二元 tuple
// - `(a,)` 为一元 tuple
//
// 注：一元 tuple `(T,)` 与 `T` 是不同类型；不做隐式兼容。
// 需要兼容时通过显式转换/构造语法完成。
TupleLiteral     ::= '(' Expr ',' ExprListOpt ')'
ExprListOpt      ::= ExprList?
ExprList         ::= Expr (',' Expr)* ','?

ArrayLiteral     ::= '[' Expr (',' Expr)* ','? ']'

// `ArrayCtorExpr`：形如 `[T; N]{ ... }`。`{}` 表示未初始化数组。
ArrayCtorExpr    ::= ArrayType '{' ArrayInitOpt '}'
ArrayInitOpt     ::= InitListOpt

// `TupleCtorExpr`：形如 `(T1, T2){ ... }`。`{}` 表示未初始化 tuple。
TupleCtorExpr    ::= TupleType '{' InitListOpt '}'

ArgListOpt       ::= ArgList?
ArgList          ::= Expr (',' Expr)* ','?

// `TypedInitExpr`：形如 `Type{ ... }`。空 `{}` 表示未初始化值。
// 同样需要在名字解析后确认 `Type` 是类型。
TypedInitExpr    ::= Type '{' InitListOpt '}'
InitListOpt      ::= InitList?
InitList         ::= InitItem (',' InitItem)* ','?
InitItem         ::= Expr | '{' InitListOpt '}'
```

说明：
- `GroupExpr` 用于分组与覆盖优先级（例如：`(a + b) * c`）。
- `TupleLiteral` 通过“是否出现逗号”区分分组与 tuple。
- `TypedInitExpr` 的合法性依赖名字解析：前缀必须是类型名。
- 类型的构造/显式转换统一为 `{}`：例如 `int{}`、`float{3.14}`。
- 形如 `f(x)` 始终是普通函数调用，不承担类型转换语义。
- 对 tuple/array 这类“类型语法不是简单名字”的类型，推荐使用 `TupleCtorExpr` / `ArrayCtorExpr`（如 `(int, double){...}`、`[int; 10]{...}`）来构造。

## 类型（最小）

```ebnf
Type             ::= TypePrimary
TypePrimary      ::= Identifier
                 |  QualifiedName
                 |  ParenType
                 |  ArrayType
                 |  TupleType

// `ParenType` 仅用于分组：`(T)` 与 `T` 等价。
ParenType        ::= '(' Type ')'

ArrayType        ::= '[' Type ';' Expr ']'
TupleType        ::= '(' Type ',' TypeListOpt ')'
TypeListOpt      ::= TypeList?
TypeList         ::= Type (',' Type)* ','?
```

注：
- `ArrayType` 的长度表达式必须是 `const` 可求值表达式；否则编译错误。
