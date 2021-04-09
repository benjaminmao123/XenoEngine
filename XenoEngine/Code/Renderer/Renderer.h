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
            const TransformComponent& mTransform;
        };

        static void Submit(const std::shared_ptr<RenderCommand>& command);

        static void DrawQuad(const TransformComponent& transform, 
                             const CameraComponent& camera, 
                             const Color& color = Color::White());

        static void Clear(unsigned char r,
                          unsigned char g,
                          unsigned char b,
                          unsigned char a,
                          GLenum flags);
        static void Clear(const Color& color, GLenum flags);

    private:
        struct RendererData
        {
            static inline const uint32_t sMaxQuads = 5000;
            static inline const uint32_t sMaxVertices = sMaxQuads * Quad::sNumVertices;
            static inline const uint32_t sMaxIndices = sMaxQuads * Quad::sNumIndices;
            static inline const uint32_t sMaxTextureUnits = 32;

            std::shared_ptr<VertexArray> mVAO;
            std::shared_ptr<VertexBuffer> mVBO;
            std::shared_ptr<ElementBuffer> mEBO;

            std::array<std::shared_ptr<Texture>, sMaxTextureUnits> mTextureUnits;
        } static inline sData;

        Renderer() = default;

        void Init() const;

        static inline std::deque<std::shared_ptr<RenderCommand>> sCommandBuffer;
        static inline BatchManager sBatchManager;

        friend class Application;
    };
}
