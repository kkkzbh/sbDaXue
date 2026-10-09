cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_COMPILER clang++)

project(kkkzbh LANGUAGES CXX)   

set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用C++模块支持
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

add_compile_options(
    -fmodules
    -fbuiltin-module-map
    -fimplicit-module-maps
    -stdlib=libc++
)

add_link_options(-stdlib=libc++)

add_executable(kkkzbh
             main.cpp)

# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})