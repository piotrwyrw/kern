// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/util/util.hpp>
#include <kern/exception/exception.hpp>

#include <fstream>
#include <sstream>

namespace kern::util
{
    std::string read_text_file(const std::string& path)
    {
        std::ifstream f(path);
        if (!f.is_open())
        {
            throw exception::Exception(std::format("Could not open file for reading: {}", path));
        }

        std::stringstream ss;
        ss << f.rdbuf();
        return ss.str();
    }
}