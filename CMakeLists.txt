cmake_minimum_required(VERSION 3.14)

set(KERN_VERSION 1.0.0 CACHE STRING "Kern Version")
set(KERN_DESCRIPTION "An Open Source C Game Development Framework" CACHE
        STRING "Kern Description")
set(KERN_AUTHOR "Vanadium Development" CACHE STRING "Kern Author")
set(KERN_COPY_YEAR 2026 CACHE STRING "Kern Release Year")

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build" CACHE STRING "Build Directory")

option(EXPORT_COMPILE_COMMANDS "Export Compile Commands JSON" ON)

message("
 /$$   /$$
| $$  /$$/
| $$ /$$/   /$$$$$$   /$$$$$$  /$$$$$$$
| $$$$$/   /$$__  $$ /$$__  $$| $$__  $$
| $$  $$  | $$$$$$$$| $$  \\__/| $$  \\ $$
| $$\\  $$ | $$_____/| $$      | $$  | $$
| $$ \\  $$|  $$$$$$$| $$      | $$  | $$
|__/  \\__/ \\_______/|__/      |__/  |__/
V${KERN_VERSION} - ${KERN_DESCRIPTION}
(C) ${KERN_COPY_YEAR} ${KERN_AUTHOR}
")

# ----------------------------------------------------------------------------------------------------------------

project(src
        VERSION ${KERN_VERSION}
        DESCRIPTION "Kern: ${KERN_DESCRIPTION}"
        LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${EXPORT_COMPILE_COMMANDS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# ---- Find all required libs ----
set(GLEW_USE_STATIC_LIBS ON)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# ---- Build the Kern Library ----
add_library(kern STATIC
        src/mm/memory_pool.c
        src/state/state.c
        src/error/error.c
        src/window/window.c)

set_target_properties(kern PROPERTIES
        C_STANDARD 17
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF)

add_library(kern::kern ALIAS kern)

target_link_libraries(kern PUBLIC OpenGL::GL GLEW::GLEW glfw)
target_include_directories(kern
        PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/vendor/cglm/include
        PRIVATE ${CMAKE_SOURCE_DIR}/private
)

# ---- Build Smoke Test Executable ----
add_executable(kern_test test/main.c)
target_link_libraries(kern_test PRIVATE kern::kern)

# ---- Build Demo Executable ----
add_executable(kern_demo demo/main.c)
target_link_libraries(kern_demo PRIVATE kern::kern)

# ---- One Target To Build Everything ----
add_custom_target(kern_all DEPENDS public kern_test kern_demo)