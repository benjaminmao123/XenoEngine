#pragma once

#include "Core/Core.h"

#include <string>
#include <glm/glm.hpp>

namespace Xeno
{
    class XENO_API Uniform
    {
    public:
        static std::string TypeToString(uint32_t type);
        static uint32_t StringToType(const std::string& type);
        [[nodiscard]] uint32_t GetType() const;

    private:
        explicit Uniform(uint32_t type);

        void SetValue(int32_t location, int32_t value);
        void SetValue(int32_t location, float value);
        void SetValue(int32_t location, const glm::vec2& value);
        void SetValue(int32_t location, const glm::vec3& value);
        void SetValue(int32_t location, const glm::vec4& value);
        void SetValue(int32_t location, const glm::mat4& value);
        void SetValue(int32_t location, const int32_t* value, uint32_t count);

        void CheckType(uint32_t type) const;

        uint32_t mType;

        friend class Shader;
    };
}

