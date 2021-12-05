#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Component/Camera.h"
#include "Graphics/Color.h"
#include "Renderer/BatchManager.h"
#include "Mesh/Quad.h"

#include <deque>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

namespace Xeno
{
    class VertexArray;
    class VertexBuffer;
    class Texture;
    class Shader;
    class ElementBuffer;
    class FrameBuffer;
    class Light;
    class Material;

    class XENO_API SceneRenderer : public NonCopyable
    {
    public:
        struct RenderCommand
        {
            enum class CommandType
            {
                MESH,
                SPRITE
            };

            CommandType mType;
            const Transform* mTransform = nullptr;
            const Mesh* mMesh = nullptr;
            const Material* mMaterial = nullptr;
        };

        static void Submit(const RenderCommand& command);

        static void RegisterLight(const Light* light);
        static void UnRegisterLight(const Light* light);

        static void SetClearColor(const Color& color);
        static const Color& GetClearColor();

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

        void ProcessEvents(const SDL_Event& event) const;
        void Render() const;
        void RenderMesh(const RenderCommand& command) const;
        void RenderSprite(const RenderCommand& command) const;

        void Draw(uint32_t topology, 
                  const VertexArray& vao, 
                  const VertexBuffer& vbo,
                  const Shader& shader) const;
        void Draw(uint32_t topology,
                  const VertexArray& vao, 
                  const ElementBuffer& ebo, 
                  const Shader& shader) const;

        void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint32_t flags) const;
        void Clear(const Color& color, uint32_t flags) const;

        static inline std::deque<RenderCommand> sCommandBuffer;
        BatchManager mBatchManager;
        static inline std::vector<const Light*> sLights;
        static inline Color sClearColor = Color::Gray();

        friend class Application;
    };
}
