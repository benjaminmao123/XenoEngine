#pragma once

#include "Core/Core.h"
#include "Component/TransformComponent.h"
#include "Utility/NonCopyable.h"
#include "Component/CameraComponent.h"
#include "Renderer/Color.h"

#include <vector>
#include <deque>

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
        struct RenderCommand
        {
            
        };

        static void Submit(const std::shared_ptr<RenderCommand>& command);

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
        } static inline sData;

        Renderer() = default;

        void Init() const;

        static inline std::deque<std::shared_ptr<RenderCommand>> sCommandBuffer;

        friend class Application;
    };
}