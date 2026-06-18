// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace kern::gfx
{
    struct from_ptr_t
    {
    };

    inline constexpr from_ptr_t from_ptr;

    template <typename T>
    struct Uniform
    {
        T data;

        explicit Uniform(T value) : data(value)
        {
        }
    };

    template <typename T, std::size_t N>
    struct Uniform<T[N]>
    {
        T data[N];

        template <typename... Args> requires
            (std::convertible_to<Args, T> && ...) && (sizeof...(Args) == N)
        explicit Uniform(Args&&... args) : data(std::forward<Args>(args)...)
        {
        }

        explicit Uniform(from_ptr_t, const T* value)
        {
            std::copy(value, value + N, data);
        }

        const T& operator[](std::size_t index) const
        {
            return data[index];
        }

        T& operator[](std::size_t index)
        {
            return data[index];
        }
    };

    template <typename T>
    struct to_uniform;

    using Uniform1f = Uniform<float>;

    template <>
    struct to_uniform<float>
    {
        using type = Uniform1f;
    };

    using Uniform2f = Uniform<float[2]>;

    template <>
    struct to_uniform<float[2]>
    {
        using type = Uniform2f;
    };

    using Uniform3f = Uniform<float[3]>;

    template <>
    struct to_uniform<float[3]>
    {
        using type = Uniform3f;
    };

    using Uniform4f = Uniform<float[4]>;

    template <>
    struct to_uniform<float[4]>
    {
        using type = Uniform4f;
    };

    using Uniform16f = Uniform<float[16]>;

    template <>
    struct to_uniform<float[16]>
    {
        using type = Uniform16f;
    };


    using Uniform1i = Uniform<int>;

    template <>
    struct to_uniform<int>
    {
        using type = Uniform1i;
    };

    using Uniform2i = Uniform<int[2]>;

    template <>
    struct to_uniform<int[2]>
    {
        using type = Uniform2i;
    };

    using Uniform3i = Uniform<int[3]>;

    template <>
    struct to_uniform<int[3]>
    {
        using type = Uniform3i;
    };

    using Uniform4i = Uniform<int[4]>;

    template <>
    struct to_uniform<int[4]>
    {
        using type = Uniform4i;
    };

    template <typename T>
    using to_uniform_t = to_uniform<T>::type;

    struct UniformVector3f : Uniform3f
    {
        explicit UniformVector3f(glm::vec3 value)
            : Uniform3f(value.x, value.y, value.z)
        {
        }
    };

    struct UniformVector2f : Uniform2f
    {
        explicit UniformVector2f(glm::vec2 value)
            : Uniform2f(value.x, value.y)
        {
        }
    };

    struct UniformMat4f : Uniform16f
    {
        explicit UniformMat4f(const glm::mat4& value)
            : Uniform16f(from_ptr, glm::value_ptr(value))
        {
        }
    };

    using AnyUniform = std::variant<Uniform1f, Uniform2f, Uniform3f, Uniform4f, Uniform16f,
                                    Uniform1i, Uniform2i, Uniform3i, Uniform4i>;
}
