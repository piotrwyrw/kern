// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <memory>

#include "timing.hpp"

namespace kern
{
    class Context
    {
        std::unique_ptr<Timing> timing_;
        bool should_close_;

    public:
        Context();

        [[nodiscard]] Timing& get_timing() const;

        [[nodiscard]] bool should_close() const;
        void request_shutdown();
    };
}
