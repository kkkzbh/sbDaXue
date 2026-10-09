cmake_minimum_required(VERSION 4.0)
project(ktuple)

set(CMAKE_CXX_STANDARD 26)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
        ktuple
)

add_library(ktuple SHARED)
target_sources(ktuple
        PUBLIC
        FILE_SET CXX_MODULES
        FILES ktuple.cppm
)