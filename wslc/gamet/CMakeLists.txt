cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

project(game_theory
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(pybind11 REQUIRED PATHS ./.venv/lib/python3.12/site-packages/pybind11)

pybind11_add_module(std main.cpp)

target_sources(std
        PRIVATE
        FILE_SET CXX_MODULES
        FILES
)

target_include_directories(std
        PRIVATE
        /usr/include/python3.12
        ./.venv/lib/python3.12/site-packages/pybind11/include
)

add_subdirectory(exp1)