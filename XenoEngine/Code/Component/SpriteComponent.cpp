#include "pch.h"
#include "Component/SpriteComponent.h"
#include "Resource/ResourceManager.h"
#include "Core/Assert.h"

Xeno::SpriteComponent::SpriteComponent(Entity* owner) :
    Component(owner)
{ }

void Xeno::SpriteComponent::LoadTexture(std::string path)
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

void Xeno::SpriteComponent::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::SpriteComponent::GetColor() const
{
    return mColor;
}

const Xeno::Texture* Xeno::SpriteComponent::GetTexture() const
{
    return mTexture;
}
