

add_library(net SHARED)
target_sources( net
        PUBLIC
        FILE_SET CXX_MODULES
        FILES src.cppm
)