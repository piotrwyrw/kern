cmake_minimum_required(VERSION 3.14)

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build" CACHE STRING "Build Directory")
option(EXPORT_COMPILE_COMMANDS "Export Compile Commands JSON" ON)

# ----------------------------------------------------------------------------------------------------------------

project(kern VERSION ${KERN_VERSION} LANGUAGES C CXX)

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
        engine/core/Engine.cpp
        engine/platform/window.cpp
        engine/exception/exception.cpp
        engine/core/context.cpp
        engine/core/timing.cpp
        engine/rendering/renderer.cpp
        engine/mesh/obj.cpp
        engine/util/fs.cpp
        engine/mesh/builtin.cpp
        engine/rendering/mesh.cpp
        engine/logging/logging.cpp
        engine/controls/controls.cpp
        engine/core/configuration.cpp
        engine/scene/camera.cpp
        include/kern/rendering/render_world.hpp
        engine/rendering/resource_manager.cpp
        engine/rendering/render_world.cpp
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

add_library(kern::kern ALIAS kern)


#
# ---- Build Demo Executable ----
#

add_executable(kern_demo demo/main.cpp)
target_link_libraries(kern_demo PRIVATE kern::kern)