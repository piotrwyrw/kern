// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/logging/logging.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace kern::log
{
    std::unique_ptr<spdlog::logger> create_logger(spdlog::level::level_enum log_level)
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(log_level);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("kern.engine.log");
        file_sink->set_level(log_level);

        auto logger = std::make_unique<spdlog::logger>(
            "Kern",
            std::initializer_list<spdlog::sink_ptr>{
                file_sink, console_sink
            });

        return logger;
    }
}