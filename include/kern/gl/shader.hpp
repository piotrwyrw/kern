// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gl.hpp>
#include <kern/gfx/uniform.hpp>

#include <string>

namespace kern::gl
{
    class ShaderProgram
    {
        GLuint program_;

        static void handle_compilation_error(GLuint shader,
                                             const std::string& debug_name,
                                             const std::string& type_name);

        static void handle_link_error(GLuint program,
                                      const std::string& debug_name);

        [[nodiscard]] static GLuint compile_shader(GLenum shader_type,
                                                   const std::string& src,
                                                   const std::string& debug_name,
                                                   const std::string& type_name);

        [[nodiscard]] static GLuint link_program(const std::string& debug_name,
                                                 GLuint fragment_shader,
                                                 GLuint vertex_shader);

    public:
        ShaderProgram(const std::string& debug_name,
                      const std::string& vertex_source,
                      const std::string& fragment_source);

        ShaderProgram(const std::string& vertex_source_path,
                      const std::string& fragment_source_path);

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& src) noexcept;
        ShaderProgram& operator=(ShaderProgram&& src) noexcept;

        ~ShaderProgram();

        [[nodiscard]] GLuint get_program() const;

        void use_program() const;

        template <typename T>
        void set_uniform(GLint location, const gfx::Uniform<T>& uniform) const = delete;

        void set_uniform(GLint location, const gfx::AnyUniform& uniform) const;
    };

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform1f& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform2f& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform3f& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform4f& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform16f& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform1i& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform2i& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform3i& uniform) const;

    template <>
    void ShaderProgram::set_uniform(GLint location, const gfx::Uniform4i& uniform) const;
}
