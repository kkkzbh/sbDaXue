cmake_minimum_required(VERSION 3.28)
project(cpp)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-fmodules-ts)

add_executable(cpp
        pre.cpp
        main.cpp
)

target_link_libraries(cpp PRIVATE stdc++exp)
