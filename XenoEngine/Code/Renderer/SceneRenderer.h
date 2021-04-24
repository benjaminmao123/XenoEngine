#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Component/Camera.h"
#include "Renderer/Graphics/Color.h"
#include "Renderer/BatchManager.h"
#include "Renderer/Mesh/Quad.h"

#include <deque>
#include <memory>
#include <SDL2/SDL.h>

namespace Xeno
{
    class VertexArray;
    class VertexBuffer;
    class Texture;
    class Shader;
    class ElementBuffer;
    class FrameBuffer;

    class XENO_API SceneRenderer : public NonCopyable
    {
    public:
        struct RenderCommand
        {
            const Transform* mTransform = nullptr;
            Color mColor = Color::White();
            const Texture* mTexture = nullptr;
            const Mesh* mMesh = nullptr;
            Shader* mShader = nullptr;
        };

        static void Submit(const RenderCommand& command);

        void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint32_t flags) const;
        void Clear(const Color& color, uint32_t flags) const;

    private:
        struct RendererData
        {
            std::shared_ptr<VertexArray> mVAO;
            std::shared_ptr<VertexBuffer> mVBO;
            std::shared_ptr<ElementBuffer> mEBO;
            std::shared_ptr<FrameBuffer> mFBO;

            Quad mScreenQuad;
        } mData;

        SceneRenderer() = default;

        void Init();

        void ProcessEvents(const SDL_Event& event);
        void Render() const;

        static inline std::deque<RenderCommand> sCommandBuffer;
        BatchManager mBatchManager;

        friend class Application;
    };
}
