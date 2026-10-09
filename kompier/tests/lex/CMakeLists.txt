add_test(
        NAME lex_v1_main
        COMMAND ${CMAKE_COMMAND}
        -D KK=$<TARGET_FILE:kk>
        -D INPUT=${CMAKE_SOURCE_DIR}/design/test/v1/main.kk
        -D EXPECT=${CMAKE_SOURCE_DIR}/tests/lex/v1/main.kk.tokens
        -P ${CMAKE_CURRENT_LIST_DIR}/run_lex_compare.cmake
)

add_test(
        NAME lex_v1_math
        COMMAND ${CMAKE_COMMAND}
        -D KK=$<TARGET_FILE:kk>
        -D INPUT=${CMAKE_SOURCE_DIR}/design/test/v1/math.kk
        -D EXPECT=${CMAKE_SOURCE_DIR}/tests/lex/v1/math.kk.tokens
        -P ${CMAKE_CURRENT_LIST_DIR}/run_lex_compare.cmake
)

add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS kk
)
