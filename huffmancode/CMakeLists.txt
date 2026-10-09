cmake_minimum_required(VERSION 3.28)
project(huffmancode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COMPILE)

add_executable(huffmancode main.cpp
        print.h
        utility.cpp
        utility.h
        priority_queue.h
        huftree.cpp
        huftree.h
        statistics.cpp
        statistics.h
        hash.h
        map.h
        fun.cpp
        fun.h
        hufio.cpp
        hufio.h
        concept.h
        menu.cpp
        menu.h
        clock.cpp
        clock.h
        time.cpp
        time
        rle.cpp
        rle.h
        lz77.cpp
        lz77.h
        string_buffer.cpp
        string_buffer.h
        deflate.cpp
        deflate.h
)