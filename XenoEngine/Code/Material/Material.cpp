#include "pch.h"
#include "Material.h"
#include "Resource/ResourceManager.h"

void Xeno::Material::SetTexture(Texture* texture)
{
    mTexture = texture;
}

const Xeno::Texture* Xeno::Material::GetTexture() const
{
    return mTexture;
}

void Xeno::Material::SetDiffuseMap(Texture* map)
{
    mDiffuseMap = map;
}

const Xeno::Texture* Xeno::Material::GetDiffuseMap() const
{
    return mDiffuseMap;
}

void Xeno::Material::SetSpecularMap(Texture* map)
{
    mSpecularMap = map;
}

const Xeno::Texture* Xeno::Material::GetSpecularMap() const
{
    return mSpecularMap;
}

void Xeno::Material::SetNormalMap(Texture* map)
{
    mNormalMap = map;
}

const Xeno::Texture* Xeno::Material::GetNormalMap() const
{
    return mNormalMap;
}

void Xeno::Material::SetHeightMap(Texture* map)
{
    mHeightMap = map;
}

const Xeno::Texture* Xeno::Material::GetHeightMap() const
{
    return mHeightMap;
}

void Xeno::Material::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::Material::GetColor() const
{
    return mColor;
}

void Xeno::Material::SetShader(Shader* shader)
{
    mShader = shader;
}

Xeno::Shader* Xeno::Material::GetShader() const
{
    return mShader;
}

void Xeno::Material::SetShininess(const float value)
{
    mShininess = value;
}

float Xeno::Material::GetShininess() const
{
    return mShininess;
}
