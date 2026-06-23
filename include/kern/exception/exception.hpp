// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>

#include <spdlog/logger.h>
#include <exception>
#include <format>
#include <functional>

namespace kern::exception
{
    class Exception : public std::exception
    {
        const std::string message_;

    public:
        explicit Exception(std::string message);

        [[nodiscard]] const char* what() const noexcept override;
    };

    void show_message_box(const Exception& e);

    void log(spdlog::logger& logger, const Exception& e);

    void handle_all(spdlog::logger& logger, const std::function<void()>& fn);

    void assert_or_throw(bool condition, const std::string& message);

    template <typename F, typename... Args>
    auto glfw_try(F&& f, Args&&... args)
    {
        static_assert(std::is_invocable<F, Args...>::value,
                      "kern::exception::glfw_try: Function not callable with the provided "
                      "arguments");

        auto check_error = []() -> void
        {
            const char* error_description;
            if (glfwGetError(&error_description) != GLFW_NO_ERROR)
            {
                throw Exception(std::format(
                    "GLFW Error: {}", error_description));
            }
        };

        if constexpr (std::is_void_v<std::invoke_result_t<F, Args...>>)
        {
            std::forward<F>(f)(std::forward<Args>(args)...);
            check_error();
        }
        else
        {
            auto value = std::forward<F>(f)(std::forward<Args>(args)...);
            check_error();
            return value;
        }
    }
}
