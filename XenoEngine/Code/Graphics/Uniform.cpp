#include "pch.h"
#include "Uniform.h"
#include "Core/Assert.h"

#include <glm/gtc/type_ptr.hpp>

Xeno::Uniform::Uniform(const uint32_t type) :
    mType(type)
{ }

void Xeno::Uniform::SetValue(const int32_t location, const int32_t value)
{
    CheckType(GL_INT);

    glUniform1i(location, value);
}

void Xeno::Uniform::SetValue(const int32_t location, const float value)
{
    CheckType(GL_FLOAT);

    glUniform1f(location, value);
}

void Xeno::Uniform::SetValue(const int32_t location, const glm::vec2& value)
{
    CheckType(GL_FLOAT_VEC2);

    glUniform2f(location, value.x, value.y);
}

void Xeno::Uniform::SetValue(const int32_t location, const glm::vec3& value)
{
    CheckType(GL_FLOAT_VEC3);

    glUniform3f(location, value.x, value.y, value.z);
}

void Xeno::Uniform::SetValue(const int32_t location, const glm::vec4& value)
{
    CheckType(GL_FLOAT_VEC4);

    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Xeno::Uniform::SetValue(const int32_t location, const glm::mat4& value)
{
    CheckType(GL_FLOAT_MAT4);

    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void Xeno::Uniform::SetValue(const int32_t location, const int32_t* value, const uint32_t count)
{
    CheckType(GL_SAMPLER_2D_ARRAY);

    glUniform1iv(location, count, value);
}

std::string Xeno::Uniform::TypeToString(const uint32_t type)
{
    switch (type)
    {
    case GL_INT:
        return "INT";
    case GL_FLOAT:
        return "FLOAT";
    case GL_FLOAT_VEC2:
        return "FLOAT2";
    case GL_FLOAT_VEC3:
        return "FLOAT3";
    case GL_FLOAT_VEC4:
        return "FLOAT4";
    case GL_FLOAT_MAT4:
        return "MAT4";
    case GL_SAMPLER_2D_ARRAY:
        return "SAMPLER_2D_ARRAY";
    default:
        break;
    }

    XN_CORE_ASSERT(false, "Uniform type not supported!")
}

uint32_t Xeno::Uniform::StringToType(const std::string& type)
{
    if (type == "INT")
        return GL_INT;
    if (type == "FLOAT")
        return GL_FLOAT;
    if (type == "FLOAT2")
        return GL_FLOAT_VEC2;
    if (type == "FLOAT3")
        return GL_FLOAT_VEC3;
    if (type == "FLOAT4")
        return GL_FLOAT_VEC4;
    if (type == "MAT4")
        return GL_FLOAT_MAT4;
    if (type == "SAMPLER_2D_ARRAY")
        return GL_SAMPLER_2D_ARRAY;

    XN_CORE_ASSERT(false, "Uniform type not supported!")
}

uint32_t Xeno::Uniform::GetType() const
{
    return mType;
}

void Xeno::Uniform::CheckType(const uint32_t type) const
{
    XN_CORE_ASSERT(mType == type, "Types must match when setting uniform!")
}
