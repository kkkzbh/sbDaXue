set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE BOOL "")
cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

project(conc LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD 1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_MODULE_CACHE_PATH "${CMAKE_BINARY_DIR}/gcm.cache")

add_compile_options(
        -fmodules
        -fmodules-ts
)

add_executable(main
        main.cpp
)

target_link_libraries(main PRIVATE
        asio
)

add_subdirectory(net)
add_subdirectory(server)
add_subdirectory(log)
add_subdirectory(benchmark)
add_subdirectory(webserver)
add_subdirectory(include)

add_executable(cxx
        cxx.cpp
)