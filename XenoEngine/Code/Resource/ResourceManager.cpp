#include "pch.h"
#include "ResourceManager.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Shader.h"

bool Xeno::ResourceManager::AddTexture(const std::shared_ptr<Texture>& texture)
{
    if (!texture->InitSuccess())
        return false;

    const auto& res = GetTexture(texture->GetPath());

    if (!res)
        sTextureCache[texture->GetPath()] = texture;

    return true;
}

Xeno::Texture* Xeno::ResourceManager::GetTexture(const std::string& path)
{
    const auto& res = sTextureCache[path];

    return res.get();
}

std::shared_ptr<Xeno::Texture> Xeno::ResourceManager::GetTextureRef(const std::string& path)
{
    const auto& res = sTextureCache[path];

    return res;
}

std::shared_ptr<Xeno::Shader> Xeno::ResourceManager::GetShaderRef(const std::string& name)
{
    const auto& res = sShaderCache[name];

    return res;
}

bool Xeno::ResourceManager::AddShader(const std::shared_ptr<Shader>& shader)
{
    if (!shader->InitSuccess())
        return false;

    const auto& res = GetShader(shader->GetName());

    if (!res)
        sShaderCache[shader->GetName()] = shader;

    return true;
}

Xeno::Shader* Xeno::ResourceManager::GetShader(const std::string& name)
{
    const auto& res = sShaderCache[name];

    return res.get();
}
