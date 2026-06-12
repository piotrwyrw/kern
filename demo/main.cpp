// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/kern.hpp>
#include <iostream>

class DemoGame : public kern::Game
{
public:
    kern::Configuration startup_config() override
    {
        return kern::Configuration{
            .title = "Kern Demo Game",
            .fullscreen = true,
            .antialiasing_samples = 4,
            .cursor_mode = kern::Hidden
        };
    }

    void on_start(kern::Context& ctx) override
    {
    }

    void on_update(kern::Context& ctx, double delta_time) override
    {
        auto& handler = ctx.get_input_handler();
        if (handler.is_key_pressed(kern::controls::Key::F))
        {
            std::cout << "Key F PRESSED!" << std::endl;
        }

        if (handler.is_key_released(kern::controls::Key::F))
        {
            std::cout << "Key F RELEASED!" << std::endl;
        }

        if (handler.cursor_moved())
        {
            std::cout << "Cursor speed: " << handler.cursor_direction().x << " | " << handler.
                cursor_direction().y << std::endl;
        }
    }

    void on_quit(kern::Context& ctx) override
    {
    }
};

int main()
{
    kern::Engine::start<DemoGame>();
    return 0;
}
