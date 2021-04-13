#pragma once

#include "Core/Core.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/ElementBuffer.h"

#include <vector>
#include <memory>

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
        VertexArray& operator=(const VertexArray& other) = delete;

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const std::shared_ptr<VertexBuffer>& vbo, 
                       const std::shared_ptr<ElementBuffer>& ebo = nullptr);

        [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const;

    private:
        uint32_t mObjectID;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<ElementBuffer> mElementBuffer;
    };
}