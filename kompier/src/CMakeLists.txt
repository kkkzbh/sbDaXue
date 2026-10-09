add_executable(kk
        kk.cpp
)

set_target_properties(kk PROPERTIES CXX_MODULE_STD ON)

target_sources(kk
        PRIVATE
        FILE_SET CXX_MODULES FILES
        basic/source.cppm
        basic/diagnostic.cppm
        frontend/lex/token.cppm
        frontend/lex/lexer.cppm
)
