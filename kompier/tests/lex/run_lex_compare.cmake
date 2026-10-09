if (NOT DEFINED KK OR NOT EXISTS "${KK}")
    message(FATAL_ERROR "KK not set or does not exist: '${KK}'")
endif()

if (NOT DEFINED INPUT OR NOT EXISTS "${INPUT}")
    message(FATAL_ERROR "INPUT not set or does not exist: '${INPUT}'")
endif()

if (NOT DEFINED EXPECT OR NOT EXISTS "${EXPECT}")
    message(FATAL_ERROR "EXPECT not set or does not exist: '${EXPECT}'")
endif()

execute_process(
        COMMAND "${KK}" lex "${INPUT}"
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
)

if (NOT rc EQUAL 0)
    message(FATAL_ERROR "kk lex failed (rc=${rc})\n${err}")
endif()

file(READ "${EXPECT}" expected)

if (NOT out STREQUAL expected)
    set(actual "${CMAKE_BINARY_DIR}/lex.actual")
    file(WRITE "${actual}" "${out}")

    find_program(DIFF_EXE diff)
    if (DIFF_EXE)
        execute_process(
                COMMAND "${DIFF_EXE}" -u "${EXPECT}" "${actual}"
                RESULT_VARIABLE diff_rc
                OUTPUT_VARIABLE diff_out
                ERROR_VARIABLE diff_err
        )
        message(FATAL_ERROR "lexer output mismatch\n${diff_out}${diff_err}")
    endif()

    message(FATAL_ERROR "lexer output mismatch (diff not available); actual saved to: ${actual}")
endif()
