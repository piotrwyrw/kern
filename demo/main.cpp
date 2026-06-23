// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/kern.hpp>

class DemoGame : public kern::Game
{
public:
    kern::Configuration startup_config() override
    {
        auto cfg = kern::default_config("Kern Demo");
        cfg.fullscreen = false;
        cfg.window_resizable = true;
        cfg.window_width = 1000;
        cfg.window_height = 700;
        cfg.cursor_mode = kern::CursorMode::Enabled;
        cfg.cursor_locked_to_center = true;

        return cfg;
    }

    void on_start(kern::Context& ctx) override
    {
        auto& logger = ctx.logger();
        logger.info("Starting {}!", ctx.get_config().title);

        // const auto shader = kern::rendering::Shader("test.a", "test.b");
        // const auto uniform = kern::rendering::Uniform2f(1, 2);
        // shader.set_uniform(4, uniform);
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
            auto delta = handler.cursor_direction();
            logger.info("Cursor location: X: {}, Y: {} | DX: {}, DY: {}", loc.x, loc.y, delta.x,
                        delta.y);
        }

        if (handler.just_resized())
        {
            logger.info("Resized to: [{}, {}]", handler.get_window_width(), handler
                        .get_window_height());
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
