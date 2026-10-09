// 不包含export module 语句的模块为匿名模块，不可导出任何符号，只可导入

// char byte short int long

import math;    // 引入命名空间 math

// 对于可导出符号的模块 允许导入再导出语句 export import math;

// 没有写出的返回类型 当作auto处理
simple_var_statement()
{
    const ten = 10;     // int
    const pi = 3.14;    // double
    const pi2 = float{3.14}; // float
    // const的语义为编译期计算
    a = 3;
    uninit_a = int{};
    // 使用未初始化的数值会编译报错
}

main()      // main函数不写返回类型
{
    simple_array_and_tuple_state(); // main可以看到下方的array_and_tuple_state符号
}

simple_array_and_tuple_state()
{
    arr = [int; 10]{}; // uninit array
    brr = [int; 10]{ 0 }; // init array
    // 允许非初始化的数组
    // 使用未初始化的值应当直接作为编译报错处理
    a = 2;
    b = 4;
    c = math::add(a,b);
    mut d = 123;  // 可变变量
    // 直接声明变量为不可变变量

    // 1: int
    // 1l: long
    // 1ul: ulong
    // 1u: uint
    // 1.: double
    // 1f: float

    tuple = (int,double,short,[int; 3]){}; // 未初始化元组
    t2 = (int,[int; 3]){ 4,{ 1,2,3 } };

    // 允许类似CTAD的行为
    t3 = (1,2,3,(1,2),[3,4,5]);
    t4 = (int{2}, 3, [int; 2]{ 1,2 });
    a2 = [1,2,3];
    a3 = [(1,2),(3,4),(5,6)];
    // 对于数组，类型统一提升到common(如果允许)

    // 不允许窄化
    // int可提升到uint
    // 数组与tuple兼容C结构体
    // float可提升到double

    // 可组合
}

// 字符串类型
string_type() -> void
{
    str = "Hello World";
    c = 'A';
    // string是结构类型，兼容C API，具体实现细节等设计结构体再考虑

}

branch_state() -> void // 声明无返回值
{
    // 待定
}
