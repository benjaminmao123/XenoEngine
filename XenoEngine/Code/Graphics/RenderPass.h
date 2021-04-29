#pragma once

#include "Core/Core.h"

namespace Xeno
{
    class FrameBuffer;

    class XENO_API RenderPass
    {
    public:
        RenderPass();

    private:
        FrameBuffer* mFrameBuffer;
    };
}