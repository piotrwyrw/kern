// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#define KERN_FORWARD_DECLARE_NS_(ns, ...)   namespace ns { class __VA_ARGS__; }
#define KERN_FORWARD_DECLARE_(c)            class c;

// spdlog
#define KERN_FORWARD_DECLARE_SPDLOG_LOGGER_ KERN_FORWARD_DECLARE_NS_(spdlog, logger)

// GLFW
#define KERN_FORWARD_DECLARE_GLFW_WINDOW_   KERN_FORWARD_DECLARE_(GLFWwindow)

// kern
#define KERN_FORWARD_DECLARE_ENGINE_        KERN_FORWARD_DECLARE_NS_(kern, Engine)
#define KERN_FORWARD_DECLARE_CONFIGURATION_ KERN_FORWARD_DECLARE_NS_(kern, Configuration)

// kern::platform
#define KERN_FORWARD_DECLARE_WINDOW_        KERN_FORWARD_DECLARE_NS_(kern::platform, Window)

// kern::controls
#define KERN_FORWARD_DECLARE_INPUT_HANDLER_ KERN_FORWARD_DECLARE_NS_(kern::controls, InputHandler)

// kern::scene
#define KERN_FORWARD_DECLARE_CAMERA_        KERN_FORWARD_DECLARE_NS_(kern::scene, Camera)
