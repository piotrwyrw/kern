// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/exception/exception.hpp>

#include <tinyfiledialogs.h>
#include <spdlog/spdlog.h>

namespace kern::exception
{
    Exception::Exception(std::string message)
        : message_(std::move(message))
    {
    }

    const char* Exception::what() const noexcept
    {
        return message_.c_str();
    }

    void show_message_box(const Exception& e)
    {
        tinyfd_messageBox("Error", e.what(), "ok", "error", 0);
    }

    void log(spdlog::logger& logger, const Exception& e)
    {
        logger.critical(e.what());
    }

    void handle_all(spdlog::logger& logger, const std::function<void()>& fn)
    {
        try
        {
            fn();
        }
        catch (Exception& e)
        {
            log(logger, e);
            show_message_box(e);
        }
    }

    void assert_or_throw(const bool condition, const std::string& message)
    {
        if (condition)
            return;

        throw Exception(std::format("Assertion Failed: {}", message));
    }
}
