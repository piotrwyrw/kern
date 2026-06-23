cmake_minimum_required(VERSION 3.14)

#
# ---- Basic Project Config ----
#

project(kern VERSION 1.0 LANGUAGES C CXX)

option(EXPORT_COMPILE_COMMANDS "Export Compile Commands JSON" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${EXPORT_COMPILE_COMMANDS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


#
# ---- Find all required libs ----
#

set(GLEW_USE_STATIC_LIBS ON)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm CONFIG REQUIRED)

#
# ---- Build Dependencies ----
#

add_subdirectory(vendor/spdlog)

add_library(tinyfiledialogs STATIC
        ${CMAKE_SOURCE_DIR}/vendor/tinyfiledialogs/tinyfiledialogs.c)


#
# ---- Build the Kern Library ----
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(kern STATIC
        engine/controls/input_handler.cpp
        engine/core/configuration.cpp
        engine/core/context.cpp
        engine/core/engine.cpp
        engine/core/timing.cpp
        engine/exception/exception.cpp
        engine/gl/frame_buffer.cpp
        engine/gl/texture.cpp
        engine/logging/logging.cpp
        engine/platform/window.cpp
        engine/gl/mesh.cpp
        engine/gl/shader.cpp
        engine/gfx/layer.cpp
        engine/scene/render_world.cpp
        engine/gfx/renderer.cpp
        engine/gfx/camera.cpp
        engine/util/util.cpp
        include/kern/types/types.hpp
)


target_link_libraries(kern PUBLIC
        spdlog::spdlog
        tinyfiledialogs
        OpenGL::GL GLEW::GLEW
        glfw
        glm::glm)

target_include_directories(kern
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include

        PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/tinyfiledialogs
        ${CMAKE_SOURCE_DIR}/vendor/stb
)

# Warn about everything but unused fields and parameters (It's annoying during development)
target_compile_options(kern PRIVATE
        -Wall -Wextra -Wpedantic)

add_library(kern::kern ALIAS kern)


#
# ---- Build Demo Executable ----
#

add_executable(kern_demo demo/main.cpp)
target_link_libraries(kern_demo PRIVATE kern::kern)