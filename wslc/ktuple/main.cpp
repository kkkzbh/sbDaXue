
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