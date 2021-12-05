#pragma once

#include "Core/Core.h"
#include "Graphics/Uniform.h"

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace Xeno
{
    class XENO_API Shader
    {
    public:
        struct ShaderSource
        {
            std::string mPath;
            uint32_t mType;
            std::string mPropsPath;
        };

        explicit Shader(std::string name);
        Shader(const std::string& name, const std::vector<ShaderSource>& sources);
        ~Shader();
        Shader& operator=(const Shader& other) = delete;

        void Bind() const;
        void Unbind() const;

        void AddShader(const ShaderSource& source);

        void SetInt(const std::string& name, int32_t value);
        void SetFloat(const std::string& name, float value);
        void SetFloat2(const std::string& name, const glm::vec2& value);
        void SetFloat2(const std::string& name, float v0, float v1);
        void SetFloat3(const std::string& name, const glm::vec3& value);
        void SetFloat3(const std::string& name, float v0, float v1, float v2);
        void SetFloat4(const std::string& name, const glm::vec4& value);
        void SetFloat4(const std::string& name, float v0, float v1, float v2, float v3);
        void SetMat4(const std::string& name, const glm::mat4& value);
        void SetSamplerArr2(const std::string& name, const int32_t* value, uint32_t count);

        [[nodiscard]] const std::string& GetName() const;
        [[nodiscard]] bool InitSuccess() const;

    private:
        [[nodiscard]] bool ProcessShader(const ShaderSource& source) const;
        [[nodiscard]] std::string ParseSource(const std::string& path) const;
        void ParseProps(const std::string& path);
        [[nodiscard ]] uint32_t CompileShader(const std::string& sourceCode, uint32_t type) const;
        [[nodiscard]] bool LinkShader(uint32_t shader) const;

        int32_t GetUniformLocation(const std::string& name);

        uint32_t mObjectID;
        std::string mName;
        bool mInitSuccess = true;
        std::unordered_map<std::string, int32_t> mUniformLocations;
        std::unordered_map<std::string, Uniform> mUniforms;
        std::unordered_map<std::string, Uniform> mExposedUniforms;
    };
}

