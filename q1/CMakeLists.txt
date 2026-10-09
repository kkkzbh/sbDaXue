cmake_minimum_required(VERSION 4.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(q1)

set(CMAKE_CXX_STANDARD 23)

add_executable(q1 main.cpp reopen/pre.cpp)

set_property(TARGET q1 PROPERTY CXX_MODULE_STD ON)