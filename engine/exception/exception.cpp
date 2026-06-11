// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/exception/exception.hpp>
#include <tinyfiledialogs.h>

#include "spdlog/spdlog.h"

kern::exception::Exception::Exception(std::string message)
    : message_(std::move(message))
{
}

const char* kern::exception::Exception::what() const noexcept
{
    return message_.c_str();
}

void kern::exception::show_message_box(const Exception& e)
{
    tinyfd_messageBox("Error", e.what(), "ok", "error", 0);
}

void kern::exception::log(spdlog::logger& logger, const Exception& e)
{
    logger.error(e.what());
}

void kern::exception::handle_all(spdlog::logger& logger, const std::function<void()>& fn)
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
