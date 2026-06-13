// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/_internal.hpp>

KERN_FORWARD_DECLARE_ENGINE_;

namespace kern
{
    class Timing
    {
        float frame_start_time_;
        float frame_delta_time_;

        void start_frame();
        void end_frame();

        friend class kern::Engine;

    public:
        Timing();

        [[nodiscard]] float get_time_now() const;

        [[nodiscard]] float get_delta_time() const;
    };
}
