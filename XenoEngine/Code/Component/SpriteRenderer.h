#pragma once

#include "Core/Core.h"
#include "Component/Renderer.h"
#include "Renderer/Graphics/Shader.h"

#include <string>
#include <vector>

namespace Xeno
{
    class Texture;
    class Sprite;

    class XENO_API SpriteRenderer final : public Renderer
    {
    public:
        explicit SpriteRenderer(Entity* owner = nullptr);

        void LoadShader(const std::string& name, const std::vector<Shader::ShaderSource>& sources);

    private:
        void OnStart() override;
        void OnRender() const override;

        Shader* mShader = nullptr;
        const Sprite* mSprite = nullptr;
    };
}