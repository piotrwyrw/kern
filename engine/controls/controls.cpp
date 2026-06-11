// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/controls/controls.hpp>
#include <kern/platform/window.hpp>

namespace kern::controls
{
    InputHandler::InputHandler(platform::Window& window)
        : window_(window),
          window_handle_(window.glfw_handle()),
          is_first_cursor_event_(true),
          cursor_curr_(0.0, 0.0),
          cursor_prev_(0.0)
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
    }

    void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_UNKNOWN || key < 0 || key > sizeof(keys_curr_))
            return;

        auto* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->keys_curr_[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    void InputHandler::cursor_callback(GLFWwindow* window, double xpos, double ypos)
    {
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

    bool InputHandler::is_key_released(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return (!keys_curr_[key_]) && keys_prev_[key_];
    }

    bool InputHandler::is_key_held(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return keys_curr_[key_] && keys_prev_[key_];
    }

    bool InputHandler::is_key_up(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return !keys_curr_[key_];
    }

    bool InputHandler::is_key_down(Key key) const
    {
        auto key_ = static_cast<int>(key);
        return keys_curr_[key_];
    }
}
