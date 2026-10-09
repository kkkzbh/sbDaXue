cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)

project(kompier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
