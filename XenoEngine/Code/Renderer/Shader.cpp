#include "pch.h"
#include "Shader.h"
#include "Core/Logger.h"

#include <fstream>

Xeno::Shader::Shader() :
    mObjectID(glCreateProgram())
{ }

Xeno::Shader::Shader(const std::vector<ShaderSource>& sources)
{
    mObjectID = glCreateProgram();

    for (const auto& source : sources)
        ProcessShader(source);
}

Xeno::Shader::~Shader()
{
    glDeleteProgram(mObjectID);
}

void Xeno::Shader::Bind() const
{
    glUseProgram(mObjectID);
}

void Xeno::Shader::Unbind() const
{
    glUseProgram(0);
}

void Xeno::Shader::AddShader(const ShaderSource& source)
{
    ProcessShader(source);
}

void Xeno::Shader::SetInt(const std::string& name, const int32_t value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniform1i(location, value);
}

void Xeno::Shader::SetFloat(const std::string& name, const float value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniform1f(location, value);
}

void Xeno::Shader::SetFloat2(const std::string& name, const glm::vec2& value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniform2f(location, value.x, value.y);
}

void Xeno::Shader::SetFloat3(const std::string& name, const glm::vec3& value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Xeno::Shader::SetFloat4(const std::string& name, const glm::vec4& value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Xeno::Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());
    glUniformMatrix4fv(location, 1, false, value_ptr(value));
}

void Xeno::Shader::ProcessShader(const ShaderSource& source)
{
    const std::string sourceCode = ParseFile(source.mPath);

    if (sourceCode.empty())
    {
        XN_CORE_ERROR("Shader failed to compile.");

        return;
    }

    switch (source.mType)
    {
    case ShaderType::VERTEX:
    case ShaderType::FRAGMENT:
        CompileShader(sourceCode, source.mType);
        break;
    default:
        XN_CORE_WARN("Shader type is not supported!");
        break;
    }
}

std::string Xeno::Shader::ParseFile(const std::string& path) const
{
    std::ifstream ifs(path);

    if (!ifs.is_open())
    {
        XN_CORE_ERROR("Failed to open file: {0}", path);

        return std::string();
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    return content;
}

void Xeno::Shader::CompileShader(const std::string& sourceCode, const ShaderType type)
{
    const char* code = sourceCode.c_str();

    const uint32_t shader = glCreateShader((GLenum)type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int32_t isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled)
    {
        int32_t maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(shader);

        XN_CORE_ERROR("Shader failed to compile: {0}", infoLog.data());

        return;
    }

    glAttachShader(mObjectID, shader);
    glLinkProgram(mObjectID);

    int32_t isLinked;
    glGetProgramiv(mObjectID, GL_LINK_STATUS, &isLinked);

    if (!isLinked)
    {
        int32_t maxLength = 0;
        glGetProgramiv(mObjectID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(mObjectID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(mObjectID);

        XN_CORE_ERROR("Shader failed to compile: {0}", infoLog.data());
    }

    glDeleteShader(shader);
}
