#include "pch.h"
#include "Component/Sprite.h"
#include "Resource/ResourceManager.h"
#include "Core/Assert.h"

Xeno::Sprite::Sprite(Entity* owner) :
    Component(owner)
{ }

void Xeno::Sprite::LoadTexture(std::string path)
{
    if (mPath == path && !mPath.empty())
        return;

    mPath = std::move(path);

    if (!ResourceManager::GetTexture(mPath))
    {
        if (!ResourceManager::AddTexture(std::make_shared<Texture>(mPath)))
            return;
    }

    mTexture = ResourceManager::GetTexture(mPath);
}

void Xeno::Sprite::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::Sprite::GetColor() const
{
    return mColor;
}

const Xeno::Texture* Xeno::Sprite::GetTexture() const
{
    return mTexture;
}

const Xeno::Quad& Xeno::Sprite::GetQuad() const
{
    return mQuad;
}
