#include "pch.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

Xeno::VertexBuffer::VertexBuffer(const uint32_t drawType) :
    mDrawType(drawType)
{
    glGenBuffers(1, &mObjectID);
}

Xeno::VertexBuffer::VertexBuffer(const uint32_t size, const uint32_t drawType) :
    mDrawType(drawType)
{
    glGenBuffers(1, &mObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, mObjectID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, mDrawType);
}

Xeno::VertexBuffer::VertexBuffer(void* data, const uint32_t size, const uint32_t drawType) :
    mDrawType(drawType)
{
    glGenBuffers(1, &mObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, mObjectID);
    glBufferData(GL_ARRAY_BUFFER, size, data, mDrawType);
}

Xeno::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &mObjectID);
}

void Xeno::VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mObjectID);
}

void Xeno::VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Xeno::VertexBuffer::PushElement(const VertexBufferLayout::VertexBufferElement& element)
{
    mLayout.PushElement(element);
}

void Xeno::VertexBuffer::SetDataNew(const void* data, const uint32_t size, const uint32_t drawType)
{
    mDrawType = drawType;

    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, mDrawType);
    Unbind();
}

void Xeno::VertexBuffer::SetDataExisting(const void* data, const uint32_t size) const
{
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    Unbind();
}

const Xeno::VertexBuffer::VertexBufferLayout& Xeno::VertexBuffer::GetLayout() const
{
    return mLayout;
}

void Xeno::VertexBuffer::SetLayout(const VertexBufferLayout& layout)
{
    mLayout = layout;
}
