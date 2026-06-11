// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <fstream>
#include <sstream>

#include <kern/util/fs.hpp>
#include <kern/exception/exception.hpp>

std::string kern::fs::read_text_file(const std::string& path)
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