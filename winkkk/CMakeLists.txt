cmake_minimum_required(VERSION 3.28)
project(winkkk)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN_SRC main.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SRC})

