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

        Shader() = default;
        Shader(const std::vector<ShaderSource>& sources);
        Shader(const std::initializer_list<ShaderSource>& sources);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetInt(const std::string& name, int32_t value);
        void SetFloat(const std::string& name, float value);
        void SetFloat2(const std::string& name, const glm::vec2& value);
        void SetFloat3(const std::string& name, const glm::vec3& value);
        void SetFloat4(const std::string& name, const glm::vec4& value);
        void SetMat4(const std::string& name, const glm::mat4& value);

    private:
        void ProcessShader(const ShaderSource& source);
        std::string ParseFile(const std::string& path) const;
        void CompileShader(const std::string& sourceCode, ShaderType type);

        uint32_t mObjectID;
    };
}

