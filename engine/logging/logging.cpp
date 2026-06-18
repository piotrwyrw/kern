// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/logging/logging.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

namespace kern::log
{
    namespace
    {
        struct LevelColor
        {
            spdlog::level::level_enum level{};
            const char* color{};
        };

        const LevelColor lv_colors_[]
        {
            {spdlog::level::trace, color::Cyan},
            {spdlog::level::debug, color::Blue},
            {spdlog::level::info, color::Green},
            {spdlog::level::warn, color::Yellow},
            {spdlog::level::err, color::Red},
            {spdlog::level::critical, color::RedBold}
        };

        void set_sink_colors(spdlog::sinks::ansicolor_stdout_sink_mt& sink)
        {
            for (auto& level_color : lv_colors_)
            {
                sink.set_color(level_color.level, level_color.color);
            }
        }
    }

    spdlog::logger create_logger(spdlog::level::level_enum log_level)
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        set_sink_colors(*console_sink);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("kern.engine.log",
            true);

        auto logger = spdlog::logger(
            "Kern",
            std::initializer_list<spdlog::sink_ptr>{
                file_sink, console_sink
            });

        logger.set_level(log_level);
        logger.set_pattern("%H:%M:%S %^[%L]%$ %v");

        return logger;
    }
}
