

add_executable(server
        server.cpp
)

target_link_libraries(server PRIVATE
        net
        utils
        log
)

add_executable(client
        client.cpp
)

target_link_libraries(client PRIVATE
        utils
        net
        log
)

add_library(utils SHARED)
target_sources( utils
        PUBLIC
        FILE_SET CXX_MODULES
        FILES utils.cppm
)
target_link_libraries(utils PRIVATE
        net
)

target_compile_definitions(utils PRIVATE
        BASE_ROOT="${CMAKE_SOURCE_DIR}/web"
)