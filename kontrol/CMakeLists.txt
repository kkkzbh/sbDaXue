cmake_minimum_required(VERSION 3.31)

project(kontrol LANGUAGES CXX)

include(CTest)
enable_testing()

include(cmake/CompilerOptions.cmake)
include(cmake/Warnings.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core DBus Widgets Test)
find_package(Qt6 6.8 QUIET COMPONENTS Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

set(KONTROL_HAS_QML OFF)
if(TARGET Qt6::Qml AND TARGET Qt6::Quick AND TARGET Qt6::QuickControls2 AND TARGET Qt6::Gui)
  set(KONTROL_HAS_QML ON)
endif()

add_library(kontrol_core STATIC
  src/core/gfx_types.h
  src/core/gfx_concepts.h
  src/core/gfx_dispatch.h
)

target_link_libraries(kontrol_core PUBLIC Qt6::Core)
set_target_properties(kontrol_core PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(kontrol_core)
kontrol_apply_warnings(kontrol_core)

add_library(kontrol_backends STATIC
  src/backends/dbus_backend.cpp
  src/backends/cli_backend.cpp
  src/backends/backend_factory.cpp
)

target_include_directories(kontrol_backends PUBLIC src)
target_link_libraries(kontrol_backends PUBLIC kontrol_core Qt6::Core Qt6::DBus)
set_target_properties(kontrol_backends PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(kontrol_backends)
kontrol_apply_warnings(kontrol_backends)

add_library(kontrol_ui STATIC
  src/ui/AppController.h
  src/ui/AppController.cpp
)

target_include_directories(kontrol_ui PUBLIC src)
target_link_libraries(kontrol_ui PUBLIC kontrol_backends Qt6::Core)
set_target_properties(kontrol_ui PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(kontrol_ui)
kontrol_apply_warnings(kontrol_ui)

add_library(kontrol_tray STATIC
  src/tray/TrayController.h
  src/tray/TrayController.cpp
)

target_include_directories(kontrol_tray PUBLIC src)
target_link_libraries(kontrol_tray PUBLIC kontrol_ui Qt6::Core Qt6::Widgets)
set_target_properties(kontrol_tray PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(kontrol_tray)
kontrol_apply_warnings(kontrol_tray)

if(KONTROL_HAS_QML)
  qt_add_executable(kontrol
    src/app/main.cpp
    src/ui/qml/qml.qrc
  )

  target_include_directories(kontrol PRIVATE src)
  target_link_libraries(kontrol
    PRIVATE
      kontrol_tray
      Qt6::Core
      Qt6::Gui
      Qt6::Qml
      Qt6::Quick
      Qt6::QuickControls2
      Qt6::Widgets
  )

  set_target_properties(kontrol PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
  kontrol_apply_compiler_options(kontrol)
  kontrol_apply_warnings(kontrol)
else()
  message(WARNING "Qt QML development packages not found. GUI target 'kontrol' is disabled; core and tests still build.")
endif()

add_executable(test_concepts tests/unit/test_concepts.cpp)
target_include_directories(test_concepts PRIVATE src)
target_link_libraries(test_concepts PRIVATE kontrol_core Qt6::Core)
set_target_properties(test_concepts PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(test_concepts)
kontrol_apply_warnings(test_concepts)
add_test(NAME test_concepts COMMAND test_concepts)

add_executable(test_mode_mapping tests/unit/test_mode_mapping.cpp)
target_include_directories(test_mode_mapping PRIVATE src)
target_link_libraries(test_mode_mapping PRIVATE kontrol_backends Qt6::Core Qt6::Test)
set_target_properties(test_mode_mapping PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(test_mode_mapping)
kontrol_apply_warnings(test_mode_mapping)
add_test(NAME test_mode_mapping COMMAND test_mode_mapping)

add_executable(test_fallback tests/integration/test_fallback.cpp)
target_include_directories(test_fallback PRIVATE src)
target_link_libraries(test_fallback PRIVATE kontrol_backends Qt6::Core Qt6::Test)
set_target_properties(test_fallback PROPERTIES CXX_STANDARD 26 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
kontrol_apply_compiler_options(test_fallback)
kontrol_apply_warnings(test_fallback)
add_test(NAME test_fallback COMMAND test_fallback)

add_test(NAME style_guard COMMAND bash ${CMAKE_SOURCE_DIR}/tools/style_guard.sh)
