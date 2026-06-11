// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/platform/window.hpp>
#include <kern/exception/exception.hpp>

kern::platform::Window::Window(const Properties& properties)
    : properties_(properties)
{
    exception::glfw_try(glfwInit);
    exception::glfw_try(glfwWindowHint, GLFW_VISIBLE, GLFW_TRUE);
    exception::glfw_try(glfwWindowHint, GLFW_VISIBLE, GLFW_FALSE);
    exception::glfw_try(glfwWindowHint, GLFW_RESIZABLE, GLFW_TRUE);
    exception::glfw_try(glfwWindowHint, GLFW_CONTEXT_VERSION_MAJOR, 3);
    exception::glfw_try(glfwWindowHint, GLFW_CONTEXT_VERSION_MINOR, 2);
    exception::glfw_try(glfwWindowHint, GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    exception::glfw_try(glfwWindowHint, GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    exception::glfw_try(glfwWindowHint, GLFW_SAMPLES, properties.antialiasing ? 4 : 0);

    this->window_ = exception::glfw_try(
        glfwCreateWindow, properties.window_width,
        properties.window_height, properties.title.c_str(),
        nullptr, nullptr);

    exception::glfw_try(glfwShowWindow, window_);
    exception::glfw_try(glfwMakeContextCurrent, window_);
    exception::glfw_try(glfwSwapInterval, 0);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        throw kern::exception::Exception(std::format(
            "GLEW Error: {}",
            reinterpret_cast<const char*>(glewGetErrorString(err))));
    }
}

void kern::platform::Window::tick()
{
    glfwPollEvents();
}

kern::platform::Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

bool kern::platform::Window::should_close() const
{
    return glfwWindowShouldClose(window_);
}

void kern::platform::Window::swap_buffers() const
{
    exception::glfw_try(glfwSwapBuffers, window_);
}