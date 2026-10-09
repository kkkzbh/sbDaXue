#
#set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE BOOL "")
#
cmake_minimum_required(VERSION 4.0.1)
#
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
#
project(CL25018 LANGUAGES CXX)
#
#set(CMAKE_CXX_MODULE_STD 1)
#
set(CMAKE_CXX_STANDARD 26)
#set(CMAKE_CXX_EXTENSIONS ON)
#
set(SRC
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/temp/pre.cpp
)

add_executable(CL25018 ${SRC})

target_compile_options(CL25018 PRIVATE
    -pedantic
    # -pedantic-errors
    -Wall
    -Wextra
    -DDEFAULT_IO_FILE_DIR="../lib/temp/"
)

#add_executable(debug
#        tmp.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/lib/temp/pre.cpp
#)
#
#target_compile_definitions(debug
#        PRIVATE DEFAULT_IO_FILE_DIR="../lib/temp/"
#)
#
#add_executable(hd
#        hd.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/lib/temp/pre.cpp
#)
#set_target_properties(hd PROPERTIES
#        CXX_STANDARD 23
#)
#
#target_compile_definitions(hd
#        PRIVATE DEFAULT_IO_FILE_DIR="../lib/temp/"
#)
#
#add_executable(random
#        random.cpp
#)
#
#add_executable(test
#        test.cpp
#)

