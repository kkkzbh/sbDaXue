

#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

import core;

namespace py = pybind11;

PYBIND11_MODULE(std,m)  // 注册为 python的std 模块
{
    py::class_<result>(m,"result")      // 注册 result 类
        .def(py::init())
        .def_readwrite("sum",&result::sum)
        .def_readwrite("have",&result::have);


    m.def("get_even_sum",&get_even_sum<int>);
    // python不能注册模板 只能显示实例化
}