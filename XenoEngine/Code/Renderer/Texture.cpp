#include "pch.h"
#include "Texture.h"
#include "Core/Logger.h"

#include <stb/stb_image.h>

Xeno::Texture::Texture(uint32_t internalFormat, uint32_t imageFormat,
                       uint32_t wrapS, uint32_t wrapT,
                       uint32_t filterMin, uint32_t filterMax,
                       bool mipMapping, int32_t mipMapLevel) :
    mInternalFormat(internalFormat), mImageFormat(imageFormat),
    mWrapS(wrapS), mWrapT(wrapT),
    mFilterMin(filterMin), mFilterMax(filterMax),
    mMipMapping(mipMapping)
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &mObjectID);
}

Xeno::Texture::Texture(std::string path,
                       uint32_t internalFormat, uint32_t imageFormat, 
                       uint32_t wrapS, uint32_t wrapT, 
                       uint32_t filterMin, uint32_t filterMax, 
                       bool mipMapping, int32_t mipMapLevel) :
    Texture(internalFormat, imageFormat,
            wrapS, wrapT,
            filterMin, filterMax,
            mipMapping, mipMapLevel)
{
    mPath = std::move(path);

    glGenTextures(1, &mObjectID);
    GenerateTexture();
}

Xeno::Texture::~Texture()
{
    glDeleteTextures(1, &mObjectID);
}

void Xeno::Texture::Bind(uint32_t slot) const
{
    glBindTextureUnit(slot, mObjectID);
}

void Xeno::Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Xeno::Texture::LoadTextureFromFile(std::string path,
                                        const uint32_t internalFormat,
                                        const uint32_t imageFormat,
                                        const uint32_t wrapS,
                                        const uint32_t wrapT,
                                        const uint32_t filterMin,
                                        const uint32_t filterMax,
                                        bool mipMapping,
                                        const int32_t mipMapLevel)
{
    mPath = std::move(path);
    mInternalFormat = internalFormat;
    mImageFormat = imageFormat;
    mWrapS = wrapS;
    mWrapT = wrapT;
    mFilterMin = filterMin;
    mFilterMax = filterMax;
    mMipMapping = mipMapping;
    mMipMapLevel = mipMapLevel;

    GenerateTexture();
}

void Xeno::Texture::SetWrapS(const uint32_t mode)
{
    mWrapS = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
    Unbind();
}

void Xeno::Texture::SetWrapT(const uint32_t mode)
{
    mWrapT = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapS);
    Unbind();
}

void Xeno::Texture::SetFilterMin(const uint32_t mode)
{
    mFilterMin = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
    Unbind();
}

void Xeno::Texture::SetFilterMax(const uint32_t mode)
{
    mFilterMax = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);
    Unbind();
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

void Xeno::Texture::GenerateTexture()
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

    Unbind();

    stbi_image_free(data);
}
