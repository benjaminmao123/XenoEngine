#include "pch.h"
#include "Renderer/Graphics/Texture.h"
#include "Core/Logger.h"
#include "Core/Assert.h"

#include <stb/stb_image.h>

Xeno::Texture::Texture(std::string path,
                       const uint32_t internalFormat, const uint32_t imageFormat,
                       const uint32_t wrapS, const uint32_t wrapT,
                       const uint32_t filterMin, const uint32_t filterMax,
                       bool mipMapping, const int32_t mipMapLevel) :
    mPath(std::move(path)),
    mInternalFormat(internalFormat), mImageFormat(imageFormat),
    mWrapS(wrapS), mWrapT(wrapT),
    mFilterMin(filterMin), mFilterMax(filterMax),
    mMipMapping(mipMapping), mMipMapLevel(mipMapLevel)
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &mObjectID);
    GenerateTextureFromFile();
}

Xeno::Texture::Texture(const uint32_t width, const uint32_t height,
                       const uint32_t internalFormat, const uint32_t imageFormat,
                       const uint32_t wrapS, const uint32_t wrapT,
                       const uint32_t filterMin, const uint32_t filterMax,
                       const bool mipMapping, const int32_t mipMapLevel,
                       const int32_t numSamples) :
    mWidth(width), mHeight(height),
    mInternalFormat(internalFormat), mImageFormat(imageFormat),
    mWrapS(wrapS), mWrapT(wrapT),
    mFilterMin(filterMin), mFilterMax(filterMax),
    mMipMapping(mipMapping), mMipMapLevel(mipMapLevel)
{
    glGenTextures(1, &mObjectID);

    if (numSamples > 1)
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, numSamples, imageFormat, width, height, GL_FALSE);
    else
    {
        glTexStorage2D(mObjectID, 1, mInternalFormat, mWidth, mHeight);

        glTextureParameteri(mObjectID, GL_TEXTURE_MIN_FILTER, mFilterMin);
        glTextureParameteri(mObjectID, GL_TEXTURE_MAG_FILTER, mFilterMax);
        glTextureParameteri(mObjectID, GL_TEXTURE_WRAP_S, mWrapS);
        glTextureParameteri(mObjectID, GL_TEXTURE_WRAP_T, mWrapT);
    }
}

Xeno::Texture::~Texture()
{
    glDeleteTextures(1, &mObjectID);
}

void Xeno::Texture::Bind(uint32_t slot) const
{
    glBindTextureUnit(slot, mObjectID);
}

void Xeno::Texture::SetData(void* data, const uint32_t size) const
{
    glTextureSubImage2D(mObjectID, 0, 0, 0, mWidth, mHeight, mImageFormat, GL_UNSIGNED_BYTE, data);
}

void Xeno::Texture::SetWrapS(const uint32_t mode)
{
    mWrapS = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
}

void Xeno::Texture::SetWrapT(const uint32_t mode)
{
    mWrapT = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapS);
}

void Xeno::Texture::SetFilterMin(const uint32_t mode)
{
    mFilterMin = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
}

void Xeno::Texture::SetFilterMax(const uint32_t mode)
{
    mFilterMax = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);
}

uint32_t Xeno::Texture::GetWidth() const
{
    return mWidth;
}

uint32_t Xeno::Texture::GetHeight() const
{
    return mHeight;
}

uint32_t Xeno::Texture::GetObjectID() const
{
    return mObjectID;
}

const std::string& Xeno::Texture::GetPath() const
{
    return mPath;
}

void Xeno::Texture::GenerateTextureFromFile()
{
    XN_CORE_INFO("Generating texture: {0}", mPath);

    int32_t width, height, channels;

    unsigned char* data = stbi_load(mPath.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        XN_CORE_ERROR("Failed to generate texture: {0}", mPath);

        return;
    }

    Bind();

    if (channels == 3)
        mImageFormat = GL_RGB;

    if (mWidth == width && mHeight == height)
    {
        glTexSubImage2D(GL_TEXTURE_2D,
                        mMipMapLevel,
                        0,
                        0,
                        mWidth,
                        mHeight,
                        mImageFormat,
                        GL_UNSIGNED_BYTE,
                        data);
    }

    mWidth = width;
    mHeight = height;

    glTexImage2D(GL_TEXTURE_2D, 
                 mMipMapLevel, 
                 mInternalFormat,
                 mWidth, 
                 mHeight, 
                 0, 
                 mImageFormat,
                 GL_UNSIGNED_BYTE, 
                 data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);

    if (mMipMapping)
        glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    XN_CORE_INFO("Successfully generated texture.\n");
}
