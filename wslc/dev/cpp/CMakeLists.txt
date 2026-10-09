cmake_minimum_required(VERSION 3.28.3)

# 项目名称和语言设置
project(cppwb
        VERSION 1.0
        LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)


