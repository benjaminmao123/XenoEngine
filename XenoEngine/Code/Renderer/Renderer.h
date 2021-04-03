#pragma once

#include "Core/Core.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/ElementBuffer.h"

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL_video.h>

namespace Xeno
{
    class XENO_API Renderer
    {
    public:
        static void DrawQuad(const glm::vec2& position, const SDL_Color& color);
        static void DrawQuad();

    private:
        Renderer() = default;

        void Init();

        static VertexArray& GetVAO();
        static VertexBuffer& GetVBO();
        static ElementBuffer& GetEBO();
        static Texture& GetTexture();
        static Shader& GetShader();

        static std::vector<float> mQuad;
        static std::vector<uint32_t> mIndices;

        friend class Application;
    };
}