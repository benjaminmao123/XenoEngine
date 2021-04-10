#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

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

        explicit Shader(std::string name);
        Shader(const std::string& name, const std::vector<ShaderSource>& sources);
        ~Shader();
        Shader& operator=(const Shader& other) = delete;

        void Bind() const;
        void Unbind() const;

        void AddShader(const ShaderSource& source);

        void SetInt(const std::string& name, int32_t value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetFloat2(const std::string& name, const glm::vec2& value) const;
        void SetFloat3(const std::string& name, const glm::vec3& value) const;
        void SetFloat4(const std::string& name, const glm::vec4& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;
        void SetIntArr(const std::string& name, int32_t* value, uint32_t count) const;

        [[nodiscard]] const std::string& GetName() const;
        [[nodiscard]] bool InitSuccess() const;

    private:
        [[nodiscard]] bool ProcessShader(const ShaderSource& source) const;
        [[nodiscard]] std::string ParseFile(const std::string& path) const;
        [[nodiscard ]] uint32_t CompileShader(const std::string& sourceCode, ShaderType type) const;
        [[nodiscard]] bool LinkShader(uint32_t shader) const;

        uint32_t mObjectID;
        std::string mName;
        bool mInitSuccess = true;
    };
}

