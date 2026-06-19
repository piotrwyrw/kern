// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/gl/shader.hpp>
#include <kern/exception/exception.hpp>
#include <kern/util/util.hpp>

namespace kern::gl
{
    void ShaderProgram::handle_compilation_error(const GLuint shader, const std::string& debug_name,
                                          const std::string& type_name)
    {
        int compile_status,
            log_length;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
        if (compile_status == GL_TRUE)
        {
            return;
        }

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        std::string log;
        log.resize(log_length);

        glGetShaderInfoLog(shader, log_length, nullptr, &log[0]);

        throw exception::Exception(std::format("ShaderProgram Error: Compilation of {} \"{}\""
                                               "failed: {}", type_name, debug_name, log));
    }

    void ShaderProgram::handle_link_error(const GLuint program, const std::string& debug_name)
    {
        int link_status,
            log_length;

        std::string log;

        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (link_status == GL_TRUE)
        {
            return;
        }

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

        log.resize(log_length);
        glGetProgramInfoLog(program, log_length, nullptr, &log[0]);

        throw exception::Exception(std::format(
            "ShaderProgram Error: Failed to link program {}: {}", debug_name, log));
    }

    GLuint ShaderProgram::compile_shader(const GLenum shader_type, const std::string& src,
                                  const std::string& debug_name,
                                  const std::string& type_name)
    {
        const char* const src_[] = {src.c_str()};
        const int src_len_[] = {static_cast<int>(src.length())};

        const GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, src_, src_len_);
        glCompileShader(shader);

        handle_compilation_error(shader, debug_name, type_name);

        return shader;
    }

    GLuint ShaderProgram::link_program(const std::string& debug_name,
                                const GLuint fragment_shader,
                                const GLuint vertex_shader)
    {
        const GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        handle_link_error(program, debug_name);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
    }

    ShaderProgram::ShaderProgram(const std::string& debug_name,
                   const std::string& vertex_source,
                   const std::string& fragment_source)
        : program_(link_program(
            debug_name,
            compile_shader(
                GL_VERTEX_SHADER,
                vertex_source,
                debug_name,
                "vertex shader"
            ),
            compile_shader(
                GL_FRAGMENT_SHADER,
                fragment_source,
                debug_name,
                "fragment shader"
            )
        ))
    {
    }

    ShaderProgram::ShaderProgram(const std::string& vertex_source_path,
                   const std::string& fragment_source_path)
        : ShaderProgram(
            std::format(
                "{}/{}",
                vertex_source_path,
                fragment_source_path
            ),
            util::read_text_file(vertex_source_path),
            util::read_text_file(fragment_source_path)
        )
    {
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& src) noexcept
        : program_(src.program_)
    {
        src.program_ = 0;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& src) noexcept
    {
        if (this == &src)
            return *this;

        glDeleteProgram(program_);

        program_ = src.program_;

        return *this;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program_);
    }

    GLuint ShaderProgram::get_program() const
    {
        return program_;
    }

    void ShaderProgram::use_program() const
    {
        glUseProgram(program_);
    }

    void ShaderProgram::set_uniform(const GLint location, const gfx::AnyUniform& uniform) const
    {
        std::visit([&](const auto& u)
        {
            set_uniform(location, u);
        }, uniform);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform1f& uniform) const
    {
        glUniform1f(location, uniform.data);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform2f& uniform) const
    {
        glUniform2f(location, uniform[0], uniform[1]);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform3f& uniform) const
    {
        glUniform3f(location, uniform[0], uniform[1], uniform[2]);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform4f& uniform) const
    {
        glUniform4f(location, uniform[0], uniform[1], uniform[2], uniform[3]);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform16f& uniform) const
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, uniform.data);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform1i& uniform) const
    {
        glUniform1i(location, uniform.data);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform2i& uniform) const
    {
        glUniform2i(location, uniform[0], uniform[1]);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform3i& uniform) const
    {
        glUniform3i(location, uniform[0], uniform[1], uniform[2]);
    }

    template <>
    void ShaderProgram::set_uniform(const GLint location, const gfx::Uniform4i& uniform) const
    {
        glUniform4i(location, uniform[0], uniform[1], uniform[2], uniform[3]);
    }
}
