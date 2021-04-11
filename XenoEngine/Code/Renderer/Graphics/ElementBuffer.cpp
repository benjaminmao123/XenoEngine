#include "pch.h"
#include "Renderer/Graphics/ElementBuffer.h"

#include <glad/glad.h>

Xeno::ElementBuffer::ElementBuffer(const uint32_t drawType) :
    mDrawType(drawType)
{
    glGenBuffers(1, &mObjectID);
}

Xeno::ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &mObjectID);
}

void Xeno::ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mObjectID);
}

void Xeno::ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Xeno::ElementBuffer::SetIndicesNew(const uint32_t* indices, const uint32_t count, const uint32_t drawType)
{
    mDrawType = drawType;
    mCount = count;

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, mDrawType);
    Unbind();
}

void Xeno::ElementBuffer::SetIndicesExisting(const uint32_t* indices, const uint32_t count)
{
    mCount = count;

    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(uint32_t), indices);
    Unbind();
}

uint32_t Xeno::ElementBuffer::GetCount() const
{
    return mCount;
}
