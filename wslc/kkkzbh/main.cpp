

// 我希望设计一个祝福人的程序，运行后以比较绚丽的方式输出 --> 苗老师新年快乐


// #include<iostream>
// #include<print>
// #include<fstream>
// #include<string>
// #include<random>
// #include<ranges>
// #include<chrono>
// #include<thread>
// #include<array>

import <iostream>;
import <print>;
import <fstream>;
import <string>;
import <random>;
import <ranges>;
import <chrono>;
import <thread>;
import <array>;

auto constexpr colors = std::array {
    "\033[31m", // 红色
    "\033[32m", // 绿色
    "\033[33m", // 黄色
    "\033[34m", // 蓝色
    "\033[35m", // 紫色
    "\033[36m", // 青色
};

auto constexpr effects = std::array {
    "\033[5m", // 闪烁
    "\033[7m", // 反白
    "\033[8m", // 消隐
    "\033[1m", // 加粗
    "\033[4m", // 下划线
};

using std::string_literals::operator ""s;
using std::chrono_literals::operator ""ms;

auto main() -> int
{
    auto ifs = std::ifstream(R"(../text.txt)");
    auto s = ""s;
    for(char c; ifs.get(c); s += c);
    std::println("{}",s);
    // 现在s里存的就是我想要输出的内容， 我希望他以比较绚丽的方式输出
    // 首先处在一个循环中
    // 随机的改变终端输出颜色
    // 随机的让****有一种滚动，流动的效果

    auto rdv = std::mt19937{ std::random_device{}() };

    std::uniform_real_distribution dist1(0.0, 200.0);

    std::println("{}",dist1(rdv));

}