include_guard(GLOBAL)

function(kontrol_apply_compiler_options target_name)
  target_compile_features(${target_name} PUBLIC cxx_std_26)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15.0)
      message(FATAL_ERROR "GCC 15+ is required for C++26 support")
    endif()
  endif()

  target_compile_options(${target_name}
    PRIVATE
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-fno-omit-frame-pointer>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-fconcepts-diagnostics-depth=3>
  )
endfunction()
