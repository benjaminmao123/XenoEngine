#include "pch.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

void Xeno::ResourceManager::AddTexture(const std::shared_ptr<Texture>& texture)
{
    const auto res = GetTexture(texture->GetPath());

    if (!res)
        GetTextureCache()[texture->GetPath()] = texture;
}

std::shared_ptr<Xeno::Texture> Xeno::ResourceManager::GetTexture(const std::string& path)
{
    auto res = GetTextureCache()[path];

    return res;
}

void Xeno::ResourceManager::AddShader(const std::shared_ptr<Shader>& shader)
{
    const auto res = GetShader(shader->GetName());

    if (!res)
        GetShaderCache()[shader->GetName()] = shader;
}

std::shared_ptr<Xeno::Shader> Xeno::ResourceManager::GetShader(const std::string& name)
{
    auto res = GetShaderCache()[name];

    return res;
}

std::unordered_map<std::string, std::shared_ptr<Xeno::Texture>>& Xeno::ResourceManager::GetTextureCache()
{
    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

    return textures;
}

std::unordered_map<std::string, std::shared_ptr<Xeno::Shader>>& Xeno::ResourceManager::GetShaderCache()
{
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

    return shaders;
}
