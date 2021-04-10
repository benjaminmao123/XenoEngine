#pragma once

#include "Core/Core.h"
#include "Component/RendererComponent.h"
#include "Renderer/Graphics/Shader.h"

#include <string>
#include <vector>

namespace Xeno
{
    class Texture;
    class MeshFilterComponent;
    class SpriteComponent;

    class XENO_API SpriteRendererComponent final : public RendererComponent
    {
    public:
        explicit SpriteRendererComponent(Entity* owner = nullptr);

        void LoadShader(const std::string& name, const std::vector<Shader::ShaderSource>& sources);

    private:
        void OnStart() override;
        void OnRender() const override;

        Shader* mShader = nullptr;
        const SpriteComponent* mSprite = nullptr;
        const MeshFilterComponent* mMeshFilter = nullptr;
    };
}