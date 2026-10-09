# trait / interface (全面解释, C++ 视角)

你现在只是在设计阶段“用 trait 约束类型”, 但 trait/interface 最终会影响很多方面: 泛型、运算符、方法调用、重载决议、代码生成、跨模块一致性等。

本文先用 C++ 类比讲清楚概念, 再给一条适合你当前项目(v0)的最小落地路线。

## 1. trait/interface 到底是什么

一个 trait/interface 可以同时被看成三种东西(三个角度都重要):

1) 约束(bound):
- "这个类型参数必须满足某些能力"。

2) 能力契约(contract):
- "如果一个类型实现了该 trait, 那么它保证提供某些操作/方法"。

3) 多态分发(polymorphism):
- 静态多态: 编译期基于类型选择实现(单态化/模板)。
- 动态多态: 运行期通过 vtable/接口表调用(类似 C++ virtual)。

## 2. 和 C++ 的对应关系

### 2.1 trait vs concept(requires)

- C++20 concept/`requires` 更像 "可计算谓词" (structural):
  - 只要某个类型能满足表达式要求, 它就满足 concept。
- Rust-style trait 更像 "名义(nominal)的能力" + 显式 impl:
  - 你需要写 `impl Trait for Type` 才算满足。

两者都能表达约束, 但工程含义不同:
- structural 更自动, 但规则复杂, 诊断也更像模板替换失败。
- nominal 更显式, 更可控, 也更适合做跨模块一致性(不容易被无意间满足/破坏)。

你项目里选择 trait 是合理的: 既能对齐 "requires 的使用体验"(调用点报错), 又能保留扩展性(用户类型也能 impl)。

### 2.2 trait vs C++ interface(纯虚基类)

- 如果你未来加入 "trait object"(动态分发), trait/interface 就会像 C++ 的抽象基类:
  - `dyn Trait` ~ `Base*` / `std::unique_ptr<Base>`
  - vtable 调用 ~ virtual dispatch

但在 v0 你完全可以只做 "静态分发"(单态化), 不做动态分发。

## 3. trait 解决的核心问题

### 3.1 泛型里如何合法地使用操作

例: 你想写一个泛型函数 `sum`。

没有 trait 时, 你写 `a + b` 会遇到一个问题:
- 对 `T` 来说, `+` 到底允不允许? 返回什么类型?

用 trait 以后:
- 你规定: 只有 `T: Add` 才能用 `+`。
- 你还能规定 `Add` 的结果类型是什么(关联类型)。

### 3.2 运算符/方法如何统一建模

一种现代做法是: 运算符也是 trait。
- `a + b` == 调用某个 trait 的实现
- 这让 "运算符可用性"、"返回类型"、"重载" 都能被 trait 系统解释。

### 3.3 给类型"外挂"方法(extension methods)

在很多语言里, trait 能提供 "你不拥有这个类型, 也能给它加能力"。

例: 你可以在自己的模块里写:
- `impl Printable for int;`
让 `int` 获得 `Printable` 能力。

这在 C++ 里通常靠 ADL/自由函数/模板特化绕来绕去。

## 4. trait 系统会牵涉到哪些语义点

### 4.1 impl 冲突与一致性(coherence)

如果允许任意模块写 `impl Trait for Type`, 很容易出现冲突:
- A 库写了 `impl Hash for int`
- B 库也写了 `impl Hash for int`
下游同时依赖 A 和 B 时就矛盾。

所以几乎所有有 trait 的语言都需要一条一致性规则。

常见策略:
- (推荐) 同一程序里, 同一个 (Trait, Type) 至多允许一个 impl。
- (可选, 更强) orphan rule: 只有当 Trait 或 Type 至少有一个是在本模块/包定义的, 才允许写 impl。

你 v0 可以先做最简单版:
- 禁止重复 impl(哪怕来自不同模块), 直接报错, 并把错误指向两个 impl 的位置。

### 4.2 选择哪个 impl(重叠 impl / 特化)

如果你以后允许 "更泛" 的 impl:

```kk
impl Printable for int;
impl<T> Printable for [T; N];
```

就会出现 "哪个更具体" 的问题。

v0 建议避免这个坑:
- 先不支持带泛型参数的 impl(只允许具体 Type)
- 或者支持也行, 但禁止任何可能重叠的 impl(保守规则)

### 4.3 名字解析/方法查找

当你有 trait 方法时, `x.foo()` 可能来自:
- 类型本身的固有方法(inherent method)
- 某个 trait 的扩展方法

你需要定义优先级和消歧方式。

典型方案:
- 先找固有方法
- 再找当前作用域引入的 trait 方法
- 冲突时要求用户写全限定形式(例如 `TraitName::foo(x)` 或类似语法)。

注：这里的 `::` 是“命名空间/限定名”的通用写法；v0 同样用于模块路径（例如 `X::Y::Z::add`）。

v0 如果 trait 是 marker, 暂时不用处理方法查找。

### 4.4 关联类型(associated types)

这是 trait/interface 走向 "真正可用" 的关键。

例: Iterator:
- `Iterator` 不只是 "能 next", 它还决定 `Item` 类型。

在 C++ 里常见写法是 `using value_type` 或 `iterator_traits`。
trait 的等价是:
- `trait Iterator { type Item; ... }`

v0 你可以先不做关联类型, 但要知道它是下一步。

### 4.5 静态分发 vs 动态分发

静态分发(单态化):
- 类似 C++ 模板
- 性能好, 但可能代码膨胀

动态分发(trait object):
- 类似 C++ 虚函数
- 需要 vtable, 运行时开销, 但避免膨胀

你现在不提供预编译, 也不提供显式实例化, v0 可以先只做静态分发。

## 5. 结合你当前语言设计(v0)的最小落地路线

你已经在 `design/spec/generics-and-constraints.md` 里决定:
- v0 有 trait/interface, 但保持简洁
- 不做显式实例化/预编译
- 可能做跨模块缓存

### v0 (建议): marker trait + 显式 impl + 约束

目标: 先让约束系统可用, 为数值/运算符/泛型打基础。

建议最小语法(已经在 grammar 里占位):

```kk
export trait Integer;

impl Integer for int;
impl Integer for long;

export div<T, U: Integer>(x: T, y: U) {
    return x / y;
}
```

语义(最小):
- trait 只是一个名字
- `impl Trait for Type;` 把 Type 加入该 trait
- 约束检查发生在调用点体验(报错指向调用)
- coherence: 禁止重复的 `(Trait, Type)` impl

### v1 (可选): 运算符由 trait 控制

目标: 让 `+ - * /` 的可用性来自 trait, 而不是编译器特判。

思路:
- 定义 `Add`, `Sub`, `Mul`, `Div` marker trait
- 编译器在类型检查 `a + b` 时, 要求 `type(a)` 满足 `Add`(以及其他你定义的规则)

这一步仍然不需要 trait 方法。

### v2 (进阶): trait 带方法签名 + impl 带方法体

目标: 真正成为 interface。

示意(未来语法, 你可按自己的风格调整):

```kk
export trait Add<Rhs> {
    Output;
    add(self, rhs: Rhs) -> Output;
}

impl Add<int> for int {
    Output = int;
    add(self, rhs: int) -> int { return self + rhs; }
}
```

这一步开始会牵涉:
- 方法查找/消歧
- 关联类型/泛型 trait
- impl 选择

## 6. 回到你之前的疑惑: "现在只涉及类型, 我理解不了"

很正常, 因为 marker trait 阶段 trait 只是在表达 "集合"。

你可以先把它当成:
- C++ concept 的一个名字
- 但 concept 的判定不是靠 `requires` 计算, 而是靠 `impl` 声明加入集合

等你以后引入 "trait 方法" 或 "运算符 trait", trait 才会从 "集合" 变成真正的 "接口"。
