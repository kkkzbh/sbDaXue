


#include <print>
#include <Python.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


auto add(int x,int y) -> int
{
    return x + y;
}

auto start() -> void
{
    std::println("Hello Python");
}

PYBIND11_MODULE(std,m)
{
    m.def("add",add,"Add two numbers");
    m.def("start",start);
}


