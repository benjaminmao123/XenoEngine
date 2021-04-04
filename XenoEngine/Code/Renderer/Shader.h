#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <vector>
#include <initializer_list>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Xeno
{
    class XENO_API Shader
    {
    public:
        enum class ShaderType
        {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER
        };

        struct ShaderSource
        {
            std::string mPath;
            ShaderType mType;
        };

        Shader();
        Shader(const std::vector<ShaderSource>& sources);
        ~Shader();
        Shader& operator=(const Shader& other) = delete;

        void Bind() const;
        void Unbind() const;

        void AddShader(const ShaderSource& source) const;

        void SetInt(const std::string& name, int32_t value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetFloat2(const std::string& name, const glm::vec2& value) const;
        void SetFloat3(const std::string& name, const glm::vec3& value) const;
        void SetFloat4(const std::string& name, const glm::vec4& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

    private:
        void ProcessShader(const ShaderSource& source) const;
        std::string ParseFile(const std::string& path) const;
        void CompileShader(const std::string& sourceCode, ShaderType type) const;

        uint32_t mObjectID;
    };
}

