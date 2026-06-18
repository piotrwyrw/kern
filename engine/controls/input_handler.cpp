// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/controls/input_handler.hpp>
#include <kern/platform/window.hpp>
#include <kern/math/math.hpp>
#include <kern/gl.hpp>

#include <glm/geometric.hpp>

namespace kern::controls
{
    InputHandler::InputHandler(platform::Window& window)
        : window_(window),
          window_handle_(window.glfw_handle()),
          is_first_cursor_event_(true),
          cursor_curr_(0.0, 0.0),
          cursor_prev_(0.0, 0.0),
          window_just_resized_(false),
          window_width_(window.get_initial_width()),
          window_height_(window.get_initial_height())

    {
        // Smuggle the handler instance to the static handler methods
        glfwSetWindowUserPointer(window_handle_, this);

        glfwSetKeyCallback(window_handle_, key_callback);
        glfwSetCursorPosCallback(window_handle_, cursor_callback);
        glfwSetWindowSizeCallback(window_handle_, size_callback);
    }

    InputHandler::~InputHandler()
    {
        glfwSetKeyCallback(window_handle_, nullptr);
        glfwSetCursorPosCallback(window_handle_, nullptr);
        glfwSetWindowSizeCallback(window_handle_, nullptr);
        glfwSetWindowUserPointer(window_handle_, nullptr);
    }

    void InputHandler::key_callback(GLFWwindow* window, const int key, int scancode,
                                    const int action, int mods)
    {
        if (key == GLFW_KEY_UNKNOWN || key < 0 || key > GLFW_KEY_LAST)
            return;

        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->keys_curr_[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    void InputHandler::cursor_callback(GLFWwindow* window, const double xpos, const double ypos)
    {
        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

        // On some platforms, GLFW still detects cursor events that are outside the window.
        // Let's make sure the cursor is actually inside before recording it.
        if (!math::is_inside_rect<double>(xpos, ypos,
                                          0, 0,
                                          handler->window_width_,
                                          handler->window_height_))
        {
            return;
        }

        handler->cursor_curr_.x = static_cast<float>(xpos);
        handler->cursor_curr_.y = static_cast<float>(ypos);

        // Avoid a cursor delta jump at the first update
        if (handler->is_first_cursor_event_)
            handler->cursor_prev_ = handler->cursor_curr_;

        handler->is_first_cursor_event_ = false;
    }

    void InputHandler::size_callback(GLFWwindow* window, const int width, const int height)
    {
        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->window_width_ = width;
        handler->window_height_ = height;
        handler->window_just_resized_ = true;
    }

    void InputHandler::swap_states()
    {
        std::memcpy(keys_prev_, keys_curr_, sizeof(keys_curr_));
        cursor_prev_ = cursor_curr_;
        window_just_resized_ = false;
    }

    bool InputHandler::is_key_pressed(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return keys_curr_[key_] && (!keys_prev_[key_]);
    }

    bool InputHandler::is_key_held(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return keys_curr_[key_] && keys_prev_[key_];
    }

    bool InputHandler::is_key_down(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return keys_curr_[key_];
    }

    bool InputHandler::is_key_released(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return (!keys_curr_[key_]) && keys_prev_[key_];
    }


    bool InputHandler::is_key_held_up(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return (!keys_curr_[key_]) && (!keys_prev_[key_]);
    }

    bool InputHandler::is_key_up(Key key) const
    {
        const auto key_ = static_cast<int>(key);
        return !keys_curr_[key_];
    }


    glm::vec2 InputHandler::cursor_position() const
    {
        return cursor_curr_;
    }

    glm::vec2 InputHandler::cursor_direction() const
    {
        const auto delta = cursor_delta();
        if (glm::length(delta) == 0.0)
            return delta;

        return glm::normalize(delta);
    }

    glm::vec2 InputHandler::cursor_delta() const
    {
        return (cursor_curr_ - cursor_prev_);
    }

    float InputHandler::cursor_speed() const
    {
        return glm::length(cursor_delta());
    }

    bool InputHandler::cursor_moved() const
    {
        return cursor_delta() != glm::vec2(0, 0);
    }

    bool InputHandler::just_resized() const
    {
        return window_just_resized_;
    }

    int InputHandler::get_window_width() const
    {
        return window_width_;
    }

    int InputHandler::get_window_height() const
    {
        return window_height_;
    }
}
