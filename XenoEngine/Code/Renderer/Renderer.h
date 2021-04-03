#pragma once

#include "Core/Core.h"
#include "Renderer/Texture.h"

#include <cstdint>

namespace Xeno
{
    class XENO_API Renderer
    {
    public:
        //static void Draw();

    private:
        Renderer() = default;
        
        static inline uint32_t mVAO;
        static inline uint32_t mVBO;
        static inline uint32_t mShader;
    };
}