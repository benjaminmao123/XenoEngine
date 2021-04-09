#include "pch.h"
#include "Renderer/Graphics/RenderBuffer.h"

#include <glad/glad.h>

Xeno::RenderBuffer::RenderBuffer()
{
    glGenRenderbuffers(1, &mObjectID);
}

Xeno::RenderBuffer::RenderBuffer(const uint32_t width, const uint32_t height,
                                 const FrameBuffer::DepthStencilFormat format)
{
    glGenRenderbuffers(1, &mObjectID);
    SetStorage(width, height, format);
}

Xeno::RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &mObjectID);
}

void Xeno::RenderBuffer::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, mObjectID);
}

void Xeno::RenderBuffer::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Xeno::RenderBuffer::SetStorage(const uint32_t width, const uint32_t height, 
                                    const FrameBuffer::DepthStencilFormat format,
                                    const int32_t numSamples)
{
    Bind();

    if (numSamples > 1)
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, numSamples, (GLenum)format, width, height);
    else
        glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)format, width, height);

    Unbind();
}

uint32_t Xeno::RenderBuffer::GetObjectID() const
{
    return mObjectID;
}
