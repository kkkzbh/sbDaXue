

pybind11_add_module(barcore
        login.cpp
)

target_sources(barcore
        PRIVATE
        FILE_SET CXX_MODULES
        FILES
        core.cpp
)