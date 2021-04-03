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

void Xeno::VertexArray::AddBuffer(const VertexBuffer* vbo, const ElementBuffer* ebo)
{
    if (!vbo)
        return;

    Bind();
    vbo->Bind();

    if (ebo)
        ebo->Bind();

    uint32_t index = 0;

    for (const auto& element : vbo->GetLayout())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index++, 
                              element.mSize, 
                              element.mType, 
                              element.mNormalized, 
                              vbo->GetLayout().GetStride(),
                              (void*)element.mOffset);
    }

    mVertexBuffers.emplace_back(*vbo);

    vbo->Unbind();
}

const std::vector<Xeno::VertexBuffer>& Xeno::VertexArray::GetVertexBuffers() const
{
    return mVertexBuffers;
}
