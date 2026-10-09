

add_library(log SHARED)
target_sources( log
        PUBLIC
        FILE_SET CXX_MODULES
        FILES log.cppm
)
target_compile_definitions(log PRIVATE
        FILE_PATH="${CMAKE_SOURCE_DIR}/log/log"
)