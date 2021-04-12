#pragma once

#include "Core/Core.h"
#include "Component/Renderer.h"

namespace Xeno
{
    class Sprite;

    class XENO_API SpriteRenderer final : public Renderer
    {
    public:
        explicit SpriteRenderer(Entity* owner = nullptr);

    private:
        void OnStart() override;
        void OnRender() const override;

        const Sprite* mSprite = nullptr;
    };
}