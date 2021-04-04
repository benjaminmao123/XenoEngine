#pragma once

#include "Core/Core.h"

#include <glad/glad.h>

namespace Xeno
{
    class XENO_API ElementBuffer
    {
    public:
        ElementBuffer(uint32_t drawType = GL_STATIC_DRAW);
        ~ElementBuffer();
        ElementBuffer& operator=(const ElementBuffer& other) = delete;

        void Bind() const;
        void Unbind() const;

        void SetIndicesNew(const uint32_t* indices, uint32_t count, uint32_t drawType = GL_STATIC_DRAW);
        void SetIndicesExisting(const uint32_t* indices, uint32_t count) const;

    private:
        uint32_t mObjectID;
        uint32_t mDrawType;
    };
}

