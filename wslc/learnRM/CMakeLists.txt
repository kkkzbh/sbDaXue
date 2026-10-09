cmake_minimum_required(VERSION 3.28)

# 禁用模块扫描 (C++26 模块暂不使用)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(learnRM LANGUAGES CXX)

# C++26 标准
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
add_compile_options(-Wall -Wextra -Wpedantic)

# =============================================================================
# 依赖管理
# =============================================================================

# Boost (asio, redis) - 使用 CONFIG 模式直接调用 BoostConfig.cmake
find_package(Boost CONFIG REQUIRED COMPONENTS system)

# PostgreSQL
find_package(PostgreSQL REQUIRED)

# CPM 包管理器
include(cmake/CPM.cmake)

# toml++ (TOML 配置文件解析)
CPMAddPackage(
    NAME tomlplusplus
    GITHUB_REPOSITORY marzer/tomlplusplus
    VERSION 3.4.0
)

# sqlpp23 (SQL 库)
CPMAddPackage(
    NAME sqlpp23
    GITHUB_REPOSITORY rbock/sqlpp23
    GIT_TAG 7cb855ec3e6f86e3a46de84d0a854bde6008ee33
)

# =============================================================================
# 主目标
# =============================================================================

add_executable(RM main.cpp)

target_include_directories(RM PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(RM PRIVATE
    Boost::system
    tomlplusplus::tomlplusplus
    sqlpp23::sqlpp23
    sqlpp23::postgresql
    ${PostgreSQL_LIBRARIES}
    pthread
)

# =============================================================================
# 安装
# =============================================================================

# 复制配置文件到构建目录
configure_file(
    ${CMAKE_SOURCE_DIR}/config/server.toml
    ${CMAKE_BINARY_DIR}/config/server.toml
    COPYONLY
)