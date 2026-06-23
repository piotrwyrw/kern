// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <format>

#include <kern/gl.hpp>
#include <kern/gfx/renderer.hpp>
#include <kern/scene/scene.hpp>
#include <kern/exception/exception.hpp>
#include <kern/core/game.hpp>
#include <kern/core/engine.hpp>
#include <kern/core/context.hpp>
#include <kern/version.hpp>
#include <kern/logging/logging.hpp>

// TODO REMOVE THIS AFTER RENDERER TESTING!!
auto CreateCubeMesh()
{
    auto mesh = std::make_unique<kern::mesh::Mesh>();

    // 24 vertices (4 per face to support per-face normals and UVs)
    // +X face (right)
    mesh->vertices.push_back({{0.5f, -0.5f, -0.5f}, {1, 0, 0}, {0, 0}});
    mesh->vertices.push_back({{0.5f, 0.5f, -0.5f}, {1, 0, 0}, {1, 0}});
    mesh->vertices.push_back({{0.5f, 0.5f, 0.5f}, {1, 0, 0}, {1, 1}});
    mesh->vertices.push_back({{0.5f, -0.5f, 0.5f}, {1, 0, 0}, {0, 1}});

    // -X face (left)
    mesh->vertices.push_back({{-0.5f, -0.5f, 0.5f}, {-1, 0, 0}, {0, 0}});
    mesh->vertices.push_back({{-0.5f, 0.5f, 0.5f}, {-1, 0, 0}, {1, 0}});
    mesh->vertices.push_back({{-0.5f, 0.5f, -0.5f}, {-1, 0, 0}, {1, 1}});
    mesh->vertices.push_back({{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 1}});

    // +Y face (top)
    mesh->vertices.push_back({{-0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0, 0}});
    mesh->vertices.push_back({{-0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0, 1}});
    mesh->vertices.push_back({{0.5f, 0.5f, 0.5f}, {0, 1, 0}, {1, 1}});
    mesh->vertices.push_back({{0.5f, 0.5f, -0.5f}, {0, 1, 0}, {1, 0}});

    // -Y face (bottom)
    mesh->vertices.push_back({{-0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0, 0}});
    mesh->vertices.push_back({{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 1}});
    mesh->vertices.push_back({{0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 1}});
    mesh->vertices.push_back({{0.5f, -0.5f, 0.5f}, {0, -1, 0}, {1, 0}});

    // +Z face (front)
    mesh->vertices.push_back({{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0}});
    mesh->vertices.push_back({{0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0}});
    mesh->vertices.push_back({{0.5f, 0.5f, 0.5f}, {0, 0, 1}, {1, 1}});
    mesh->vertices.push_back({{-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 1}});

    // -Z face (back)
    mesh->vertices.push_back({{0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 0}});
    mesh->vertices.push_back({{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0}});
    mesh->vertices.push_back({{-0.5f, 0.5f, -0.5f}, {0, 0, -1}, {1, 1}});
    mesh->vertices.push_back({{0.5f, 0.5f, -0.5f}, {0, 0, -1}, {0, 1}});

    // 12 triangles (2 per face), CCW winding order
    for (uint32_t i = 0; i < 6; ++i)
    {
        uint32_t base = i * 4;
        mesh->tri_faces.push_back({base + 0, base + 1, base + 2});
        mesh->tri_faces.push_back({base + 0, base + 2, base + 3});
    }

    return mesh;
}

namespace kern
{
    Engine::Engine(std::unique_ptr<Game> game, const Configuration& config)
        : logger_(log::create_logger(spdlog::level::trace)),
          game_(std::move(game)),
          config_(config),
          window_(platform::Window(config)),
          renderer_(gfx::Renderer(window_)),
          context_(*this, window_, config, logger_),
          resources_(gl::ResourceManager(logger_)),
          world_(scene::Scene()),
          camera_(gfx::Camera(
              *this,
              glm::dvec3(0, 0, 0),
              glm::dvec3(0, 0, 1),M_PI))
    {
        // TODO REMOVE THIS AFTER RENDERER TESTING!!
        // const auto mesh = CreateCubeMesh();
        // std::unique_ptr<rendering::GpuMesh> gpu_mesh = std::make_unique<rendering::GpuMesh>(*mesh);
        // auto a = resources_->add_mesh(std::move(gpu_mesh));

        exception::handle_all(logger_, [&]() -> void
        {
            run();
        });
    }

    Engine::~Engine()
    {
        logger_.info("Kern shutting down. Goodbye!");
    }

    const platform::Window& Engine::get_window() const
    {
        return window_;
    }

    bool Engine::should_close() const
    {
        return context_.is_shutdown_requested() || window_.should_close();
    }

    void Engine::run()
    {
        game_->on_start(context_);

        auto& timing = context_.get_timing();

        while (!should_close())
        {
            timing.start_frame();

            window_.handle_events();

            game_->on_update(context_, timing.get_delta_time());
            renderer_.render(world_, resources_, camera_);

            window_.swap_buffers();

            timing.end_frame();
        }

        game_->on_quit(context_);
    }
}
