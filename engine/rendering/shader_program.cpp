// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <kern/gl.hpp>
#include <kern/rendering/shader_program.hpp>
#include <kern/exception/exception.hpp>
#include <kern/util/fs.hpp>

namespace kern::rendering
{
    void ShaderProgram::handle_compilation_errors(GLuint shader, const std::string& debug_name,
                                                  const std::string& type_name) const
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

    GLuint ShaderProgram::compile_shader(GLenum shader_type, const std::string& src,
                                         const std::string& debug_name,
                                         const std::string& type_name) const
    {
        const char* const src_[] = {src.c_str()};
        const int src_len_[] = {static_cast<int>(src.length())};

        const GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, src_, src_len_);
        glCompileShader(shader);
        handle_compilation_errors(shader, debug_name, type_name);

        return shader;
    }

    GLuint ShaderProgram::link_program(const std::string& debug_name, GLuint fragment_shader,
                                       GLuint vertex_shader) const
    {
        int link_status,
            log_length;
        std::string log;

        const GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (link_status == GL_TRUE)
        {
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            return program;
        }

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

        log.resize(log_length);
        glGetProgramInfoLog(program, log_length, nullptr, &log[0]);

        throw exception::Exception(std::format(
            "ShaderProgram Error: F1ailed to link program from vertex shader ({}) and fragment "
            "shader ({}) \"{}\": {}", vertex_shader, fragment_shader, debug_name, log));
    }

    ShaderProgram::ShaderProgram(const std::string& debug_name,
                                 const std::string& vertex_source,
                                 const std::string& fragment_source)
        : program_(link_program(
            debug_name,
            compile_shader(GL_VERTEX_SHADER, vertex_source, debug_name, "vertex shader"),
            compile_shader(GL_FRAGMENT_SHADER, fragment_source, debug_name, "fragment shader")
        ))
    {
    }

    ShaderProgram::ShaderProgram(const std::string& vertex_source_path,
                                 const std::string& fragment_source_path)
        : ShaderProgram(
            std::format("{}/{}", vertex_source_path,
                        fragment_source_path
            ), vertex_source_path, fragment_source_path)
    {
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program_);
    }
}
