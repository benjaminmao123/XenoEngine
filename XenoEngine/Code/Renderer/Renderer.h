#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Component/CameraComponent.h"
#include "Renderer/Graphics/Color.h"
#include "Renderer/BatchManager.h"
#include "Renderer/Mesh/Quad.h"

#include <vector>
#include <deque>
#include <memory>
#include <array>

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
            const TransformComponent* mTransform = nullptr;
            const Color& mColor = Color::White();
            const Texture* mTexture = nullptr;
            const Mesh* mMesh = nullptr;
            const Shader* mShader = nullptr;
        };

        static void Submit(const RenderCommand& command);

        static void Clear(unsigned char r,
                          unsigned char g,
                          unsigned char b,
                          unsigned char a,
                          GLenum flags);
        static void Clear(const Color& color, GLenum flags);

    private:
        struct RendererData
        {
            std::shared_ptr<VertexArray> mVAO;
            std::shared_ptr<VertexBuffer> mVBO;
            std::shared_ptr<ElementBuffer> mEBO;
        } mData;

        Renderer() = default;

        void Init();
        void Render();

        static inline std::deque<RenderCommand> sCommandBuffer;
        BatchManager mBatchManager;

        friend class Application;
    };
}
