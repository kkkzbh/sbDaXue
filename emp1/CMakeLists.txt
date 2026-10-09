cmake_minimum_required(VERSION 3.28.2)
project(emp1)

set(CMAKE_CXX_STANDARD 23)

add_executable(emp1 main.cpp
        pre.cpp
)

target_compile_options(emp1 PUBLIC
        -lstdc++exp
)

target_link_options(emp1 PUBLIC
        -lstdc++exp
)