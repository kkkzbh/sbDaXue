cmake_minimum_required(VERSION 4.0.1)

project(test
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(pybind11 REQUIRED PATHS ./.venv/lib/python3.12/site-packages/pybind11)

pybind11_add_module(std
        login.cpp
)

target_sources(std
        PRIVATE
        FILE_SET CXX_MODULES
        FILES
        core.cpp
)

target_include_directories(std
        PRIVATE
        /usr/include/python3.12
        ./.venv/lib/python3.12/site-packages/pybind11/include
)