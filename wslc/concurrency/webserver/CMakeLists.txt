

add_executable(httpserver
        http.cpp
)

target_link_libraries(httpserver PRIVATE
        net
        utils
        log
)

add_executable(sync-asiohttp
        sync-asiohttp.cpp
)
target_link_libraries(sync-asiohttp PRIVATE
        asio
)