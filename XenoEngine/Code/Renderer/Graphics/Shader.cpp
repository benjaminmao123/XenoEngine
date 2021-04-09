#include "pch.h"
#include "Renderer/Graphics/Shader.h"
#include "Core/Logger.h"

#include <fstream>

Xeno::Shader::Shader(std::string name) :
    mObjectID(glCreateProgram()),
    mName(std::move(name))
{ }

Xeno::Shader::Shader(const std::string& name, const std::vector<ShaderSource>& sources) :
    Shader(name)
{
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

void Xeno::Shader::AddShader(const ShaderSource& source) const
{
    ProcessShader(source);
}

void Xeno::Shader::SetInt(const std::string& name, const int32_t value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform1i(location, value);
}

void Xeno::Shader::SetFloat(const std::string& name, const float value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform1f(location, value);
}

void Xeno::Shader::SetFloat2(const std::string& name, const glm::vec2& value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform2f(location, value.x, value.y);
}

void Xeno::Shader::SetFloat3(const std::string& name, const glm::vec3& value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform3f(location, value.x, value.y, value.z);
}

void Xeno::Shader::SetFloat4(const std::string& name, const glm::vec4& value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Xeno::Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniformMatrix4fv(location, 1, false, value_ptr(value));
}

void Xeno::Shader::SetIntArr(const std::string& name, int32_t* value, uint32_t count) const
{
    const int32_t location = glGetUniformLocation(mObjectID, name.c_str());

    if (location == -1)
    {
        XN_CORE_WARN("Uniform: {0} does not exist in the current shader.", name);

        return;
    }

    glUniform1iv(location, count, value);
}

const std::string& Xeno::Shader::GetName() const
{
    return mName;
}

void Xeno::Shader::ProcessShader(const ShaderSource& source) const
{
    XN_CORE_INFO("Processing shader: {0}", source.mPath);

    const std::string sourceCode = ParseFile(source.mPath);

    if (sourceCode.empty())
    {
        XN_CORE_ERROR("Shader failed to compile.");

        return;
    }

    XN_CORE_INFO("Successfully parsed shader.");

    switch (source.mType)
    {
        case ShaderType::VERTEX:
        case ShaderType::FRAGMENT:
        {
            const uint32_t shader = CompileShader(sourceCode, source.mType);
            if (shader != -1)
                if (LinkShader(shader))
                    XN_CORE_INFO("Successfully processed shader.\n");
            break;
        }
        default:
            XN_CORE_WARN("Shader type is not supported!");
            break;
    }
}

std::string Xeno::Shader::ParseFile(const std::string& path) const
{
    XN_CORE_INFO("Parsing file...", path);

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

uint32_t Xeno::Shader::CompileShader(const std::string& sourceCode, const ShaderType type) const
{
    XN_CORE_INFO("Compiling shader...");

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

        return -1;
    }

    XN_CORE_INFO("Successfully compiled shader.");

    return shader;
}

bool Xeno::Shader::LinkShader(const uint32_t shader) const
{
    XN_CORE_INFO("Linking shader...");

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
        glDeleteShader(shader);
        glDeleteProgram(mObjectID);

        XN_CORE_ERROR("Shader failed to compile: {0}", infoLog.data());

        return false;
    }

    XN_CORE_INFO("Successfully linked shader.");

    glDeleteShader(shader);

    return true;
}
