#include "pch.h"
#include "Material.h"
#include "Resource/ResourceManager.h"

Xeno::Material::Material() :
    mShader(ResourceManager::GetShaderRef("Default Shader"))
{ }

void Xeno::Material::SetTexture(const std::shared_ptr<Texture>& texture)
{
    mTexture = texture;
}

const Xeno::Texture* Xeno::Material::GetTexture() const
{
    return mTexture.get();
}

void Xeno::Material::SetDiffuseMap(const std::shared_ptr<Texture>& map)
{
    mDiffuseMap = map;
}

const Xeno::Texture* Xeno::Material::GetDiffuseMap() const
{
    return mDiffuseMap.get();
}

void Xeno::Material::SetSpecularMap(const std::shared_ptr<Texture>& map)
{
    mSpecularMap = map;
}

const Xeno::Texture* Xeno::Material::GetSpecularMap() const
{
    return mSpecularMap.get();
}

void Xeno::Material::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::Material::GetColor() const
{
    return mColor;
}

void Xeno::Material::SetShader(const std::shared_ptr<Shader>& shader)
{
    mShader = shader;
}

Xeno::Shader* Xeno::Material::GetShader() const
{
    return mShader.get();
}

void Xeno::Material::SetShininess(const float value)
{
    mShininess = value;
}

float Xeno::Material::GetShininess() const
{
    return mShininess;
}
