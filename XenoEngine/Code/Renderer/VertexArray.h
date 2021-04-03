#pragma once

#include "Core/Core.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"

#include <vector>

namespace Xeno
{
    class XENO_API VertexArray
    {
    public:
        enum class BufferTypes
        {
            VERTEX,
            ELEMENT,
            FRAME
        };

        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const VertexBuffer* vbo, const ElementBuffer* ebo);

        [[nodiscard]] const std::vector<VertexBuffer>& GetVertexBuffers() const;

    private:
        uint32_t mObjectID;

        std::vector<VertexBuffer> mVertexBuffers;
    };
}