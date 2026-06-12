// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <exception>
#include <format>
#include <functional>
#include <glfw/glfw3.h>
#include <spdlog/logger.h>

namespace kern::exception
{
    class Exception : public std::exception
    {
        const std::string message_;

    public:
        Exception(std::string message);

        [[nodiscard]] const char* what() const noexcept override;
    };

    void show_message_box(const Exception& e);

    void log(spdlog::logger& logger, const Exception& e);

    void handle_all(spdlog::logger& logger, const std::function<void()>& fn);

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

        if constexpr (std::is_void<std::invoke_result_t<F, Args...>>::value)
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
