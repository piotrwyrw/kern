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
        return {.window_resizable = true};
    }

    void on_start(kern::Context& ctx) override
    {
        auto& logger = ctx.logger();
        logger.info("Starting {}!", ctx.get_config().title);
    }

    void on_update(kern::Context& ctx, float delta_time) override
    {
        auto& handler = ctx.get_input_handler();
        auto& logger = ctx.logger();

        if (handler.is_key_pressed(kern::controls::Key::F))
        {
            logger.info("Key F PRESSED!");
        }

        if (handler.is_key_released(kern::controls::Key::F))
        {
            logger.info("Key F RELEASED!");
        }

        if (handler.cursor_moved())
        {
            auto loc = handler.cursor_position();
            logger.info("Cursor location: X: {}, Y: {}", loc.x, loc.y);
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
