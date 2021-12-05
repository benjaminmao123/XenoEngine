#include "pch.h"
#include "FrameBuffer.h"
#include "Graphics/Texture.h"
#include "Core/Window.h"
#include "Graphics/RenderBuffer.h"
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

void Xeno::FrameBuffer::Bind(const uint32_t mode) const
{
    glBindFramebuffer(mode, mObjectID);
    glViewport(0, 0, mProps.mWidth, mProps.mHeight);
}

void Xeno::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Xeno::FrameBuffer::Invalidate()
{
    XN_CORE_INFO("Generating Framebuffer...");

    if (mObjectID)
    {
        glDeleteFramebuffers(1, &mObjectID);

        for (const auto& i : mColorAttachments)
            delete i;

        mColorAttachments.clear();
        mColorAttachmentBuffer.clear();
    }

    glGenFramebuffers(1, &mObjectID);
    Bind();

    mColorAttachments.resize(mProps.mColorFormats.size());

    for (std::size_t i = 0; i < mProps.mColorFormats.size(); ++i)
    {
        const Texture::TextureProperties props =
        {
            "Color Attachment " + std::to_string(i),
            mProps.mWidth, mProps.mHeight,
            mProps.mColorFormats[i], mProps.mColorFormats[i]
        };

        mColorAttachments[i] = new Texture(props, mProps.mNumSamples, false);

        if (mProps.mNumSamples > 1)
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

        mColorAttachmentBuffer.emplace_back(GL_COLOR_ATTACHMENT0 + i);
    }

    if (mProps.mDepthStencilFormat != GL_NONE)
    {
        mRenderBuffer->SetStorage(mProps.mWidth, mProps.mHeight, mProps.mDepthStencilFormat, mProps.mNumSamples);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer->GetObjectID());
    }

    if (!mColorAttachmentBuffer.empty())
        glDrawBuffers(mColorAttachments.size(), &mColorAttachmentBuffer[0]);
    else
        glDrawBuffer(GL_NONE);

    XN_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete.\n")

    XN_CORE_INFO("Successfully generated Framebuffer.\n");

    Unbind();
}

void Xeno::FrameBuffer::Resize(const uint32_t width, const uint32_t height)
{
    if (!width || !height || width > sMaxFrameBufferSize || height > sMaxFrameBufferSize)
    {
        XN_CORE_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);

        return;
    }

    mProps.mWidth = width;
    mProps.mHeight = height;

    Invalidate();
}

uint32_t Xeno::FrameBuffer::GetWidth() const
{
    return mProps.mWidth;
}

uint32_t Xeno::FrameBuffer::GetHeight() const
{
    return mProps.mHeight;
}

const Xeno::Texture* Xeno::FrameBuffer::GetColorAttachment(const uint32_t index) const
{
    XN_CORE_ASSERT(index < mColorAttachments.size())

    return mColorAttachments[index];
}
