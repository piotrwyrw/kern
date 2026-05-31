cmake_minimum_required(VERSION 4.2.2)

project(kern)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Find all required libs ----
set(GLEW_USE_STATIC_LIBS ON)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(kern_deps INTERFACE)
target_link_libraries(kern_deps INTERFACE OpenGL::GL GLEW::GLEW glfw)
target_include_directories(kern_deps INTERFACE ${GLEW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/kern ${CMAKE_SOURCE_DIR}/vendor/cglm/include)

function(use_kern_dependencies target)
    target_link_libraries(${target} PUBLIC kern_deps)
endfunction()

# ---- Build all modules ----
add_subdirectory(kern/core)
add_subdirectory(kern/display)

add_library(kern STATIC
        $<TARGET_OBJECTS:kern_core>
        $<TARGET_OBJECTS:kern_display>)

use_kern_dependencies(kern)

# ---- Build Smoke Test Executable ----
add_executable(kern_test test/main.c)
target_link_libraries(kern_test PRIVATE kern)

# ---- Build Demo Executable ----
add_executable(kern_demo demo/main.c)
target_link_libraries(kern_demo PRIVATE kern)