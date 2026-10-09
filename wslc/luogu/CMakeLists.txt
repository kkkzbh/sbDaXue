cmake_minimum_required(VERSION 3.28.3)

project(luogu)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
        SRC
        main.cpp
)

add_executable(luogu ${SRC})