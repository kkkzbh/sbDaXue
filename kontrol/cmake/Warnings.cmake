include_guard(GLOBAL)

function(kontrol_apply_warnings target_name)
  target_compile_options(${target_name}
    PRIVATE
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wall>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wextra>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wpedantic>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wconversion>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wshadow>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wnon-virtual-dtor>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wold-style-cast>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wcast-align>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wunused>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wnull-dereference>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wdouble-promotion>
      $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wformat=2>
  )
endfunction()
