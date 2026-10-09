cmake_minimum_required(VERSION 3.28.3)

project(Torch LANGUAGES CXX CUDA)

enable_language(CXX)
enable_language(CUDA)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED)
set(CMAKE_PREFIX_PATH "C:/LibTorch/Debug")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(Torch main.cu)

set_target_properties(Torch PROPERTIES
    CUDA_ARCHITECTURES native
)
target_link_libraries(Torch "${TORCH_LIBRARIES}")

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET Torch POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:Torch>)
endif()

#if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#    set_target_properties(Torch PROPERTIES
#            CUDA_SEPARABLE_COMPILATION ON)
#    set(CMAKE_PREFIX_PATH C:/LibTorch/Debug)
#    find_package(Torch REQUIRED)
#    target_link_libraries(Torch "${TORCH_LIBRARIES}")
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#    find_package(Python3 REQUIRED)
#    set(CMAKE_PREFIX_PATH "/usr/local/libtorch")
#    find_package(Torch REQUIRED)
#    target_link_libraries(Torch "${TORCH_LIBRARIES}")
#endif()

