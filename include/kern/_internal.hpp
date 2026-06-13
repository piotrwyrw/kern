// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#define KERN_FORWARD_DECLARE_NS_(ns, ...) \
    namespace ns { class __VA_ARGS__; }

#define KERN_FORWARD_DECLARE_(...) \
    class __VA_ARGS__;


// spdlog
#define KERN_FORWARD_DECLARE_SPDLOG_LOGGER_ \
    KERN_FORWARD_DECLARE_NS_(spdlog, logger)

// GLFW
#define KERN_FORWARD_DECLARE_GLFW_WINDOW_ \
    KERN_FORWARD_DECLARE_(GLFWwindow)

// kern
#define KERN_FORWARD_DECLARE_ENGINE_ \
    KERN_FORWARD_DECLARE_NS_(kern, Engine)
#define KERN_FORWARD_DECLARE_CONFIGURATION_ \
    KERN_FORWARD_DECLARE_NS_(kern, Configuration)

// kern::platform
#define KERN_FORWARD_DECLARE_WINDOW_ \
    KERN_FORWARD_DECLARE_NS_(kern::platform, Window)

// kern::controls
#define KERN_FORWARD_DECLARE_INPUT_HANDLER_ \
    KERN_FORWARD_DECLARE_NS_(kern::controls, InputHandler)

// kern::rendering
#define KERN_FORWARD_DECLARE_CAMERA_ \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, Camera)
#define KERN_FORWARD_DECLARE_GPU_MESH \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, GpuMesh)
#define KERN_FORWARD_DECLARE_RENDER_OBJECT \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, RenderObject)
#define KERN_FORWARD_DECLARE_RENDER_WORLD \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, RenderWorld)
#define KERN_FORWARD_DECLARE_RESOURCE_MANAGER \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, ResourceManager)
#define KERN_FORWARD_DECLARE_RENDERER \
    KERN_FORWARD_DECLARE_NS_(kern::rendering, Renderer)
