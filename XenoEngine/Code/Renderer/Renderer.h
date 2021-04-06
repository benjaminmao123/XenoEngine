#pragma once

#include "Core/Core.h"
#include "Component/TransformComponent.h"
#include "Utility/NonCopyable.h"
#include "Component/CameraComponent.h"
#include "Renderer/Color.h"

#include <vector>
#include <glm/glm.hpp>

namespace Xeno
{
    class VertexArray;
    class VertexBuffer;
    class Texture;
    class Shader;
    class ElementBuffer;

    class XENO_API Renderer : public NonCopyable
    {
    public:
        static void DrawQuad(const TransformComponent& transform, 
                             const CameraComponent& camera, 
                             const Color& color = Color::White());

    private:
        struct RendererData
        {
            std::shared_ptr<VertexArray> mVAO;
            std::shared_ptr<VertexBuffer> mVBO;
            std::shared_ptr<ElementBuffer> mEBO;
            std::vector<float> mQuad;
            std::vector<uint32_t> mIndices;
        } static mData;

        Renderer() = default;

        void Init();

        friend class Application;
    };
}