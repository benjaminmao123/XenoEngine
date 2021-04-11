#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Component/Camera.h"
#include "Renderer/Graphics/Color.h"
#include "Renderer/BatchManager.h"
#include "Renderer/Mesh/Quad.h"

#include <deque>
#include <memory>

namespace Xeno
{
    class VertexArray;
    class VertexBuffer;
    class Texture;
    class Shader;
    class ElementBuffer;

    class XENO_API SceneRenderer : public NonCopyable
    {
    public:
        struct RenderCommand
        {
            const Transform* mTransform = nullptr;
            Color mColor = Color::White();
            const Texture* mTexture = nullptr;
            const Mesh* mMesh = nullptr;
            const Shader* mShader = nullptr;
        };

        static void Submit(const RenderCommand& command);

        void Clear(unsigned char r,
                   unsigned char g,
                   unsigned char b,
                   unsigned char a,
                   GLenum flags) const;
        void Clear(const Color& color, GLenum flags) const;

    private:
        struct RendererData
        {
            std::shared_ptr<VertexArray> mVAO;
            std::shared_ptr<VertexBuffer> mVBO;
            std::shared_ptr<ElementBuffer> mEBO;
        } mData;

        SceneRenderer() = default;

        void Init();
        void Render();

        static inline std::deque<RenderCommand> sCommandBuffer;
        BatchManager mBatchManager;

        friend class Application;
    };
}
