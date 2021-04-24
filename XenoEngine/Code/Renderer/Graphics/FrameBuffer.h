#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <glad/glad.h>
#include <vector>

namespace Xeno
{
    class RenderBuffer;

    class XENO_API FrameBuffer
    {
    public:
        struct FrameBufferProperties
        {
            uint32_t mWidth;
            uint32_t mHeight;

            std::vector<uint32_t> mColorFormats;
            uint32_t mDepthStencilFormat;

            uint32_t mNumSamples = 1;
        };

        explicit FrameBuffer(FrameBufferProperties props);
        ~FrameBuffer();

        void Bind(uint32_t mode = GL_FRAMEBUFFER) const;
        void Unbind() const;

        void Invalidate();
        void Resize(uint32_t width, uint32_t height);

        [[nodiscard]] uint32_t GetWidth() const;
        [[nodiscard]] uint32_t GetHeight() const;

        [[nodiscard]] uint32_t GetColorAttachment(uint32_t index) const;

    private:
        uint32_t mObjectID = 0;

        FrameBufferProperties mProps;
        std::vector<uint32_t> mColorAttachments;
        std::vector<uint32_t> mColorAttachmentBuffer;
        RenderBuffer* mRenderBuffer;

        static inline const uint32_t sMaxFrameBufferSize = 8192;
    };
}