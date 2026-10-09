 
# ktuple

在继承`std::tuple`的基础上，扩展了一些功能。

## ktuple类

- 完全兼容`std::tuple`, 包括`std::get`, `std::make_tuple`
- 支持 `>> <<` 流重载符, 目前仅以`空格`作为`sep`
- 支持以`tp[3i]`的形式下标访问, 行为如同`std::get<3>(tp)`, 启用`using namespace ktuple_literals`打开该功能, 目前该下标只能显式的以`xi`(带有后缀i)的字面量写出
- 可以使用`make_ktuple`构造
- 支持`format`, 行为如同`format`一个`std::tuple`

## kpack类

- 主要是用于便捷性的打包, 辅助结构化绑定等使用
- 拥有一个全局定制点对象`pack`, 所有的`kpack`实例视为等同的一个实例
- `pack[1,2,std::vector{ 1,2,3 }]` 的行为如同 `make_ktuple(1,2,std::vector{ 1,2,3 })`
- `pack(1,2,3)` 的行为如同 `make_ktuple(std::ref(1),std::ref(2),std::ref(3))`或`std::tie(1,2,3)` 当然这里是错误用法，圆括号`()`的`pack`仅能pack一组左值

### 举例
```cpp
    auto [a,b] = pack[3,4]; // a = 3, b = 4
    pack(a,b) = pack[b,a]; // a = 4, b = 3 
```

## kcmp与kweight类

主要用于元组相关的**排序操作**上，方便的快速指定元组键排序的**优先级**，以及是不降**序**还是不升**序**排序

## 入门

```cpp

#include <print>
#include <vector>
#include <algorithm>

import ktuple;

using namespace ktuple_literals;

auto main() -> int
{

    auto a = std::vector<ktuple<int,double,ktuple<int,int>>> {
                { 5,  2.,    { 7, 4 } },
                { 1,   .66,  { 4, 1 } },
                { 9, 88.1,   { 7, 12 } }
    };

    std::ranges::sort(a,kcmp{ std::ignore,std::greater{} });
    // 按第二个参数降序排序 忽略第一个参数 缺省忽略第三个参数
    for(auto const& tp : a) {
        std::println("{}",tp);
    }
    std::println("------------------------");
    std::ranges::sort(a,kcmp{ std::ignore,std::ignore,pack[std::ignore,std::less{}]});
    // 按第三个参数升序排序 忽略第一个和第二个参数 第三个是元组 按第二个参数升序
    for(auto const& tp : a) {
        std::println("{}",tp);
    }
    std::println("------------------------");
    std::ranges::sort(a,kcmp{ kweight{ 2i,1i },pack[std::greater{}],std::greater{} });
    // 设定优先级 按第二个参数(元组)的第一个参数降序排序，缺省忽略该元组其他元素 然后第一个参数降序排序
    //          没有定义该第二个参数元组的优先级 按缺省来
    for(auto const& tp : a) {
        std::println("{}",tp);
    }
    std::println("------------------------");
    std::ranges::sort(a,kcmp{ kweight{ pack[2i,pack[1i,0i]],0i },pack[std::less{},std::greater{}],std::greater{} });
    // 设定内置元组的优先级 先排第二个参数元组，然后元组内优先级是先1参数less后0参数greater，然后在按第0个元素按降序(greater)
    for(auto const& tp : a) {
        std::println("{}",tp);
    }
    std::println("------------------------");
    auto tp0 = a[0]; // 获取元组
    std::println("格式化ktuple tp0 = {}",tp0);
    std::println("索引ktuple tp0[2] = {}",tp0[2i]);
    std::println("保持get接口 tp0[2] = {}",std::get<2>(tp0));

    return 0;
}

```

以上代码的打印结果为
```angular2html

(9, 88.1, (7, 12))
(5, 2, (7, 4))
(1, 0.66, (4, 1))
------------------------
(1, 0.66, (4, 1))
(5, 2, (7, 4))
(9, 88.1, (7, 12))
------------------------
(9, 88.1, (7, 12))
(5, 2, (7, 4))
(1, 0.66, (4, 1))
------------------------
(1, 0.66, (4, 1))
(5, 2, (7, 4))
(9, 88.1, (7, 12))
------------------------
格式化ktuple tp0 = (1, 0.66, (4, 1))
索引ktuple tp0[2] = (4, 1)
保持get接口 tp0[2] = (4, 1)

```