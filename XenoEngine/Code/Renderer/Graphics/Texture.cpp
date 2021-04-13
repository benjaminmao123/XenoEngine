#include "pch.h"
#include "Texture.h"
#include "Core/Logger.h"
#include "Core/Assert.h"

#include <stb/stb_image.h>
#include <utility>

Xeno::Texture::Texture(TextureProperties props, const int32_t mipMapLevel) :
    mProps(std::move(props))
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &mObjectID);

    mInitSuccess = GenerateTextureFromFile(mipMapLevel);
}

Xeno::Texture::Texture(void* data, TextureProperties props, const int32_t mipMapLevel) :
    mProps(std::move(props))
{
    stbi_set_flip_vertically_on_load(1);

    glGenTextures(1, &mObjectID);

    SetDataNew(data, mProps, mipMapLevel);
}

Xeno::Texture::Texture(TextureProperties props, const int32_t numSamples, const bool fixed) :
    mProps(std::move(props))
{
    glGenTextures(1, &mObjectID);
    Bind();

    if (numSamples > 1)
        glTexImage2DMultisample(GL_TEXTURE_2D, 
                                numSamples, 
                                (uint32_t)mProps.mInternalFormat, 
                                mProps.mWidth, mProps.mHeight, 
                                fixed);
    else
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     (uint32_t)mProps.mInternalFormat,
                     mProps.mWidth,
                     mProps.mHeight,
                     0,
                     (uint32_t)mProps.mImageFormat,
                     mProps.mDataType,
                     nullptr);

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mProps.mFilterMax);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapT);
    }
}

Xeno::Texture::~Texture()
{
    glDeleteTextures(1, &mObjectID);
}

void Xeno::Texture::Bind(const uint32_t slot) const
{
    glBindTextureUnit(slot, mObjectID);
}

void Xeno::Texture::SetDataNew(void* data, TextureProperties props, const int32_t mipMapLevel)
{
    mProps = std::move(props);

    Bind();

    glTexImage2D(GL_TEXTURE_2D,
                 mipMapLevel,
                 (uint32_t)mProps.mInternalFormat,
                 mProps.mWidth,
                 mProps.mHeight,
                 0,
                 (uint32_t)mProps.mImageFormat,
                 mProps.mDataType,
                 data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mProps.mFilterMax);

    if (mipMapLevel)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void Xeno::Texture::SetDataExisting(void* data, const int32_t mipMapLevel) const
{
    Bind();

    glTexSubImage2D(GL_TEXTURE_2D,
                    mipMapLevel,
                    0,
                    0,
                    mProps.mWidth,
                    mProps.mHeight,
                    (uint32_t)mProps.mImageFormat,
                    mProps.mDataType,
                    data);
}

void Xeno::Texture::SetWrapS(const uint32_t mode)
{
    mProps.mWrapS = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
}

void Xeno::Texture::SetWrapT(const uint32_t mode)
{
    mProps.mWrapT = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapS);
}

void Xeno::Texture::SetFilterMin(const uint32_t mode)
{
    mProps.mFilterMin = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
}

void Xeno::Texture::SetFilterMax(const uint32_t mode)
{
    mProps.mFilterMax = mode;
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mProps.mFilterMax);
}

uint32_t Xeno::Texture::GetWidth() const
{
    return mProps.mWidth;
}

uint32_t Xeno::Texture::GetHeight() const
{
    return mProps.mHeight;
}

uint32_t Xeno::Texture::GetObjectID() const
{
    return mObjectID;
}

const std::string& Xeno::Texture::GetPath() const
{
    return mProps.mPath;
}

bool Xeno::Texture::InitSuccess() const
{
    return mInitSuccess;
}

bool Xeno::Texture::GenerateTextureFromFile(const int32_t mipMapLevel)
{
    XN_CORE_INFO("Generating texture: {0}", mProps.mPath);

    int32_t width, height, channels;

    uint8_t* data = stbi_load(mProps.mPath.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        XN_CORE_ERROR("Failed to generate texture: {0}", mProps.mPath);

        return false;
    }

    mProps.mWidth = width;
    mProps.mHeight = height;

    SetDataNew(data, mProps, mipMapLevel);

    stbi_image_free(data);

    XN_CORE_INFO("Successfully generated texture.\n");

    return true;
}
