// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <spdlog/spdlog.h>

#include "spdlog/sinks/ansicolor_sink.h"

namespace kern::log
{
    std::unique_ptr<spdlog::logger> create_logger(spdlog::level::level_enum log_level);
}

/**
 * ANSI Color Escape Codes Copied from <code>spdlog::sinks::ansicolor_sink</code>
 * to make them accessible without a sink instance
 */
namespace kern::log::color
{
    // Formatting codes
    inline auto Reset = "\033[m";
    inline auto Bold = "\033[1m";
    inline auto Dark = "\033[2m";
    inline auto Underline = "\033[4m";
    inline auto Blink = "\033[5m";
    inline auto Reverse = "\033[7m";
    inline auto Concealed = "\033[8m";
    inline auto ClearLine = "\033[K";

    // Foreground colors
    inline auto Black = "\033[30m";
    inline auto Red = "\033[31m";
    inline auto Green = "\033[32m";
    inline auto Yellow = "\033[33m";
    inline auto Blue = "\033[34m";
    inline auto Magenta = "\033[35m";
    inline auto Cyan = "\033[36m";
    inline auto White = "\033[37m";

    /// Background colors
    inline auto OnBlack = "\033[40m";
    inline auto OnRed = "\033[41m";
    inline auto OnGreen = "\033[42m";
    inline auto OnYellow = "\033[43m";
    inline auto OnBlue = "\033[44m";
    inline auto OnMagenta = "\033[45m";
    inline auto OnCyan = "\033[46m";
    inline auto OnWhitehite = "\033[47m";

    /// Bold colors
    inline auto YellowBold = "\033[33m\033[1m";
    inline auto RedBold = "\033[31m\033[1m";
    inline auto BoldOnRed = "\033[1m\033[41m";
}
