#include "pch.h"
#include "Renderer/Graphics/FrameBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Core/Window.h"
#include "Renderer/Graphics/RenderBuffer.h"
#include "Core/Logger.h"
#include "Core/Assert.h"

#include <glad/glad.h>
#include <utility>

Xeno::FrameBuffer::FrameBuffer(FrameBufferProperties props) :
    mProps(std::move(props)),
    mRenderBuffer(new RenderBuffer)
{
    Invalidate();
}

Xeno::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &mObjectID);

    for (const auto& i : mColorAttachments)
        delete i;

    delete mRenderBuffer;
}

void Xeno::FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, mObjectID);
    glViewport(0, 0, mProps.mWidth, mProps.mHeight);
}

void Xeno::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Xeno::FrameBuffer::Invalidate()
{
    if (mObjectID)
    {
        glDeleteFramebuffers(1, &mObjectID);

        for (const auto& i : mColorAttachments)
            delete i;

        mColorAttachments.clear();
    }

    glGenFramebuffers(1, &mObjectID);
    Bind();

    mColorAttachments.resize(mProps.mColorFormats.size());

    for (std::size_t i = 0; i < mProps.mColorFormats.size(); ++i)
    {
        mColorAttachments[i] = new Texture("color_attachment",
                                           mProps.mWidth,
                                           mProps.mHeight,
                                           (GLenum)mProps.mColorFormats[i],
                                           (GLenum)mProps.mColorFormats[i],
                                           GL_CLAMP_TO_EDGE,
                                           GL_CLAMP_TO_EDGE,
                                           GL_LINEAR,
                                           GL_LINEAR,
                                           false,
                                           0,
                                           mProps.mSamples);

        if (mProps.mSamples > 1)
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0 + i,
                                   GL_TEXTURE_2D_MULTISAMPLE,
                                   mColorAttachments[i]->GetObjectID(),
                                   0);
        else
            glFramebufferTexture2D(GL_FRAMEBUFFER, 
                                   GL_COLOR_ATTACHMENT0 + i, 
                                   GL_TEXTURE_2D, 
                                   mColorAttachments[i]->GetObjectID(), 
                                   0);
    }

    if (mProps.mDepthStencilFormat != DepthStencilFormat::NONE)
    {
        mRenderBuffer->SetStorage(mProps.mWidth, mProps.mHeight, mProps.mDepthStencilFormat, mProps.mSamples);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer->GetObjectID());
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        XN_CORE_ERROR("Framebuffer is not complete.");

    Unbind();
}

void Xeno::FrameBuffer::Resize(const uint32_t width, const uint32_t height)
{
    if (!width || !height || width > sMaxFrameBufferSize || height > sMaxFrameBufferSize)
    {
        XN_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);

        return;
    }

    mProps.mWidth = width;
    mProps.mHeight = height;

    Invalidate();
}

uint32_t Xeno::FrameBuffer::GetColorAttachmentObjectID(const uint32_t index) const
{
    XN_CORE_ASSERT(index < mColorAttachments.size());

    return mColorAttachments[index]->GetObjectID();
}
