#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <glad/glad.h>
#include <vector>

namespace Xeno
{
    class Texture;
    class RenderBuffer;

    class XENO_API FrameBuffer
    {
    public:
        enum class ColorFormat
        {
            RGB = GL_RGB,
            RGBA8 = GL_RGBA8,
        };

        enum class DepthStencilFormat
        {
            NONE = GL_NONE,
            DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8
        };

        struct FrameBufferProperties
        {
            uint32_t mWidth;
            uint32_t mHeight;
            uint32_t mSamples = 1;

            std::vector<ColorFormat> mColorFormats;
            DepthStencilFormat mDepthStencilFormat;
        };

        explicit FrameBuffer(FrameBufferProperties props);
        ~FrameBuffer();

        void Bind() const;
        void Unbind() const;

        void Invalidate();
        void Resize(uint32_t width, uint32_t height);

    private:
        uint32_t mObjectID;
        FrameBufferProperties mProps;
        std::vector<Texture*> mColorAttachments;
        RenderBuffer* mRenderBuffer;

        static inline const uint32_t sMaxFrameBufferSize = 8192;
    };
}