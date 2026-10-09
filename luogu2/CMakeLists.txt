cmake_minimum_required(VERSION 3.27)
project(luogu)

set(CMAKE_CXX_STANDARD 26)

add_compile_options(-fmodules-ts)

add_executable(luogu
        main.cpp
        pre.cpp
)

target_link_libraries(luogu PRIVATE stdc++exp)
