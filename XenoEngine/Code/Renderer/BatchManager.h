#pragma once

#include "Core/Core.h"

#include <cstdint>

namespace Xeno
{
    // TODO
    class XENO_API BatchManager
    {
    public:
        struct Batch
        {

            
            uint32_t mTextureIndex;
        };

        BatchManager() = default;

        void StartBatch(const Batch& batch);
        void EndBatch();
        void FlushBatch();
    };
}