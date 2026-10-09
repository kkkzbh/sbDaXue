
// 酒吧博弈游戏的Python绑定接口
// 这个文件把C++的核心代码包装成Python可以调用的模块

#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

import bar.core;  // 导入我们写的核心模块

namespace py = pybind11;

// 创建名为 barcore 的Python模块
PYBIND11_MODULE(barcore,m)
{
    // 把C++的config结构体暴露给Python
    // Python里就可以创建config对象并设置各种参数
    py::class_<config>(m,"config")
        .def(py::init())  // 让Python可以创建config对象
        .def_readwrite("n",&config::n)                      // 总人数
        .def_readwrite("t",&config::t)                      // 仿真天数
        .def_readwrite("c",&config::c)                      // 酒吧容量
        .def_readwrite("random_ratio",&config::random_ratio)     // 随机策略比例
        .def_readwrite("adaptive_ratio",&config::adaptive_ratio) // 自适应策略比例
        .def_readwrite("kw",&config::kw)                    // 移动平均记忆长度
        .def_readwrite("seed",&config::seed);               // 随机种子

    // 把C++的result结构体暴露给Python
    // Python可以接收仿真结果并分析数据
    py::class_<result>(m,"result")
        .def(py::init())  // 让Python可以创建result对象
        .def_readwrite("attendance",&result::attendance)        // 每天出勤人数
        .def_readwrite("avg_rewards",&result::avg_rewards)      // 每天平均奖励
        .def_readwrite("cum_rewards",&result::cum_rewards);     // 累积奖励

    // 把核心仿真函数暴露给Python
    // Python调用 barcore.sim(配置) 就能运行仿真
    m.def("sim",&sim,"酒吧博弈仿真主函数");
}