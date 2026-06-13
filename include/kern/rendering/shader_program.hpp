// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <string>

namespace kern::rendering
{
    class ShaderProgram
    {
    private:
        GLuint program_;

        void handle_compilation_errors(GLuint shader, const std::string& debug_name,
                                       const std::string& type_name) const;

        [[nodiscard]] GLuint compile_shader(GLenum shader_type, const std::string& src,
                                            const std::string& debug_name,
                                            const std::string& type_name) const;

        [[nodiscard]] GLuint link_program(const std::string& debug_name, GLuint fragment_shader,
            GLuint vertex_shader) const;

    public:
        ShaderProgram(const std::string& debug_name,
                      const std::string& vertex_source,
                      const std::string& fragment_source);

        ShaderProgram(const std::string& vertex_source_path,
                      const std::string& fragment_source_path);

        ~ShaderProgram();

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&&) = delete;
    };
}
