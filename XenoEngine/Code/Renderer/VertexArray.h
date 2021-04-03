#pragma once

#include "Core/Core.h"
#include "Renderer/VertexBuffer.h"

#include <vector>

namespace Xeno
{
    class XENO_API VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const VertexBuffer& buffer);

        [[nodiscard]] const std::vector<VertexBuffer>& GetVertexBuffers() const;

    private:
        uint32_t mObjectID;

        std::vector<VertexBuffer> mVertexBuffers;
    };
}