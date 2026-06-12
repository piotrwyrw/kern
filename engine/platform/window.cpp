// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/platform/window.hpp>
#include <kern/exception/exception.hpp>

namespace kern::platform
{
    Window::Window(const Configuration& config)
        : config_(config)
    {
        exception::glfw_try(glfwInit);
        exception::glfw_try(glfwWindowHint, GLFW_VISIBLE, GLFW_TRUE);
        exception::glfw_try(glfwWindowHint, GLFW_VISIBLE, GLFW_FALSE);
        exception::glfw_try(glfwWindowHint, GLFW_RESIZABLE, config.window_resizable);
        exception::glfw_try(glfwWindowHint, GLFW_CONTEXT_VERSION_MAJOR, 3);
        exception::glfw_try(glfwWindowHint, GLFW_CONTEXT_VERSION_MINOR, 2);
        exception::glfw_try(glfwWindowHint, GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        exception::glfw_try(glfwWindowHint, GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        exception::glfw_try(glfwWindowHint, GLFW_SAMPLES, config.antialiasing_samples);

        GLFWmonitor* monitor = nullptr;
        int width = config.window_width;
        int height = config.window_height;

        bool is_fullscreen = config.fullscreen || config.window_width <= 0
            || config.window_height <= 0;

        if (is_fullscreen)
        {
            monitor = exception::glfw_try(glfwGetPrimaryMonitor);
            if (monitor == nullptr)
            {
                throw exception::Exception("Failed to detect any monitor");
            }

            const GLFWvidmode* video_mode = exception::glfw_try(glfwGetVideoMode, monitor);
            if (video_mode == nullptr)
            {
                throw exception::Exception(
                    "Failed to retrieve the video mode of the primary monitor.");
            }

            width = video_mode->width;
            height = video_mode->height;
        }

        this->window_ = exception::glfw_try(glfwCreateWindow, width, height,
                                            config.title.c_str(), monitor, nullptr);

        exception::glfw_try(glfwShowWindow, window_);
        exception::glfw_try(glfwMakeContextCurrent, window_);
        exception::glfw_try(glfwSwapInterval, 0);

        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            throw exception::Exception(std::format(
                "GLEW Error: {}",
                reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        int cursor_mode;
        switch (config.cursor_mode)
        {
        case CursorMode::Enabled:
            cursor_mode = GLFW_CURSOR_NORMAL;
            break;
        case CursorMode::Hidden:
            cursor_mode = GLFW_CURSOR_HIDDEN;
            break;
        case CursorMode::Disabled:
            cursor_mode = GLFW_CURSOR_DISABLED;
            break;
        }

        exception::glfw_try(glfwSetInputMode, window_, GLFW_CURSOR, cursor_mode);
        input_handler_ = std::make_unique<controls::InputHandler>(*this);
    }

    void Window::handle_events() const
    {
        input_handler_->swap_states();
        glfwPollEvents();
    }

    Window::~Window()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    bool Window::should_close() const
    {
        return glfwWindowShouldClose(window_);
    }

    void Window::swap_buffers() const
    {
        exception::glfw_try(glfwSwapBuffers, window_);
    }

    GLFWwindow* Window::glfw_handle() const
    {
        return window_;
    }

    const controls::InputHandler& Window::input_handler() const
    {
        return *input_handler_;
    }
}
