cmake_minimum_required(VERSION 3.28.3)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    project(luogu LANGUAGES CXX CUDA)
else()
    project(luogu)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    enable_language(CXX)
    enable_language(CUDA)
endif()

set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CUDA_STANDARD 17)
# set(CMAKE_CUDA_STANDARD_REQUIRED ON)

    find_package(Python3 REQUIRED)
    set(CMAKE_PREFIX_PATH "/usr/local/libtorch")
    set(Torch_DIR "/usr/local/libtorch/share/cmake/Torch")
    find_package(Torch REQUIRED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

endif()

add_executable(luogu
        lib/temp/pre.cpp
        main.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

    set_target_properties(luogu PROPERTIES
            CUDA_ARCHITECTURES native
    )

    target_link_libraries(luogu PRIVATE "${TORCH_LIBRARIES}")

endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-stdlib=libstdc++)
    include_directories(/user/include/c++/14)
    add_compile_options(-fmodules)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libstdc++")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fmodules-ts)
    target_link_libraries(luogu PRIVATE stdc++exp)
endif()

