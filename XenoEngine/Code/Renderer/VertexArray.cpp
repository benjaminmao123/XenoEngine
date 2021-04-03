#include "pch.h"
#include "VertexArray.h"

Xeno::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mObjectID);
}

Xeno::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mObjectID);
}

void Xeno::VertexArray::Bind() const
{
    glBindVertexArray(mObjectID);
}

void Xeno::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void Xeno::VertexArray::AddVertexBuffer(const VertexBuffer& buffer)
{
    Bind();
    buffer.Bind();

    uint32_t index = 0;

    for (const auto& element : buffer.GetLayout())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index++, 
                              element.mSize, 
                              element.mType, 
                              element.mNormalized, 
                              buffer.GetLayout().GetStride(), 
                              (void*)element.mOffset);
    }

    mVertexBuffers.emplace_back(buffer);

    buffer.Unbind();
}

const std::vector<Xeno::VertexBuffer>& Xeno::VertexArray::GetVertexBuffers() const
{
    return mVertexBuffers;
}
