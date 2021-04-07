#include "pch.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

void Xeno::ResourceManager::AddTexture(const std::shared_ptr<Texture>& texture)
{
    const auto& res = GetTexture(texture->GetPath());

    if (!res)
        sTextureCache[texture->GetPath()] = texture;
}

Xeno::Texture* Xeno::ResourceManager::GetTexture(const std::string& path)
{
    const auto& res = sTextureCache[path];

    return res.get();
}

void Xeno::ResourceManager::AddShader(const std::shared_ptr<Shader>& shader)
{
    const auto& res = GetShader(shader->GetName());

    if (!res)
        sShaderCache[shader->GetName()] = shader;
}

Xeno::Shader* Xeno::ResourceManager::GetShader(const std::string& name)
{
    const auto& res = sShaderCache[name];

    return res.get();
}
