// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/controls/controls.hpp>
#include <kern/platform/window.hpp>

#include <glm/geometric.hpp>

#include "kern/kern.hpp"

namespace kern::controls
{
    InputHandler::InputHandler(platform::Window& window)
        : window_(window),
          window_handle_(window.glfw_handle()),
          is_first_cursor_event_(true),
          cursor_curr_(0.0, 0.0),
          cursor_prev_(0.0, 0.0)
    {
        // Smuggle the handler instance to the static handler methods
        glfwSetWindowUserPointer(window_handle_, this);

        glfwSetKeyCallback(window_handle_, key_callback);
        glfwSetCursorPosCallback(window_handle_, cursor_callback);
    }

    InputHandler::~InputHandler()
    {
        glfwSetKeyCallback(window_handle_, nullptr);
        glfwSetCursorPosCallback(window_handle_, nullptr);
        glfwSetWindowUserPointer(window_handle_, nullptr);
    }

    void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_UNKNOWN || key < 0 || key > GLFW_KEY_LAST)
            return;

        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->keys_curr_[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    void InputHandler::cursor_callback(GLFWwindow* window, double xpos, double ypos)
    {
        int width, height;
        exception::glfw_try(glfwGetWindowSize, window, &width, &height);

        // On some platforms, GLFW still detects cursor events that are outside the window.
        // Let's make sure the cursor is actually inside before recording it.
        if (!math::is_inside_rect<double>(xpos, ypos, 0, 0, width, height))
        {
            return;
        }

        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->cursor_curr_.x = xpos;
        handler->cursor_curr_.y = ypos;

        // Avoid a cursor delta jump at the first update
        if (handler->is_first_cursor_event_)
            handler->cursor_prev_ = handler->cursor_curr_;

        handler->is_first_cursor_event_ = false;
    }

    void InputHandler::swap_states()
    {
        std::memcpy(keys_prev_, keys_curr_, sizeof(keys_curr_));
        cursor_prev_ = cursor_curr_;
    }

    bool InputHandler::is_key_pressed(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return keys_curr_[key_] && (!keys_prev_[key_]);
    }

    bool InputHandler::is_key_held(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return keys_curr_[key_] && keys_prev_[key_];
    }

    bool InputHandler::is_key_down(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return keys_curr_[key_];
    }


    bool InputHandler::is_key_released(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return (!keys_curr_[key_]) && keys_prev_[key_];
    }


    bool InputHandler::is_key_held_up(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return (!keys_curr_[key_]) && (!keys_prev_[key_]);
    }

    bool InputHandler::is_key_up(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return !keys_curr_[key_];
    }


    glm::dvec2 InputHandler::cursor_position() const
    {
        return cursor_curr_;
    }

    glm::dvec2 InputHandler::cursor_direction() const
    {
        auto delta = cursor_delta();
        if (glm::length(delta) == 0.0)
            return delta;

        return glm::normalize(delta);
    }

    glm::dvec2 InputHandler::cursor_delta() const
    {
        return (cursor_curr_ - cursor_prev_);
    }

    double InputHandler::cursor_speed() const
    {
        return glm::length(cursor_delta());
    }

    bool InputHandler::cursor_moved() const
    {
        return cursor_delta() != glm::dvec2(0.0, 0.0);
    }
}
