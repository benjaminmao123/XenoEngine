#pragma once

#include "Core/Core.h"
#include "Renderer/Graphics/FrameBuffer.h"

namespace Xeno
{
    class XENO_API RenderBuffer
    {
    public:
        RenderBuffer();
        explicit RenderBuffer(uint32_t width, uint32_t height,
                              FrameBuffer::DepthStencilFormat format);
        ~RenderBuffer();

        void Bind() const;
        void Unbind() const;

        void SetStorage(uint32_t width, uint32_t height,
                        FrameBuffer::DepthStencilFormat format,
                        int32_t numSamples = 1);

        [[nodiscard]] uint32_t GetObjectID() const;

    private:
        uint32_t mObjectID;
    };
}