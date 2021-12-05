#include "pch.h"
#include "Texture.h"
#include "Core/Logger.h"
#include "Core/Assert.h"

#include <stb/stb_image.h>
#include <utility>

Xeno::Texture::Texture(TextureProperties props, const bool mipMap, const int32_t mipMapLevel) :
    mProps(std::move(props))
{
    glGenTextures(1, &mObjectID);

    mInitSuccess = GenerateTextureFromFile(mipMap, mipMapLevel);
}

Xeno::Texture::Texture(void* data, TextureProperties props, const bool mipMap, const int32_t mipMapLevel) :
    mProps(std::move(props))
{
    glGenTextures(1, &mObjectID);

    SetDataNew(data, mProps, mipMap, mipMapLevel);
}

Xeno::Texture::Texture(TextureProperties props, 
                       const int32_t numSamples,
                       const bool fixed,
                       const bool mipMap) :
    mProps(std::move(props))
{
    glGenTextures(1, &mObjectID);
    Bind(false);

    if (numSamples > 1)
        glTexImage2DMultisample(GL_TEXTURE_2D, 
                                numSamples, 
                                mProps.mInternalFormat, 
                                mProps.mWidth, mProps.mHeight, 
                                fixed);
    else
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     mProps.mInternalFormat,
                     mProps.mWidth,
                     mProps.mHeight,
                     0,
                     mProps.mImageFormat,
                     mProps.mDataType,
                     nullptr);

        if (mipMap)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mProps.mFilterMax);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapT);
    }
}

Xeno::Texture::~Texture()
{
    glDeleteTextures(1, &mObjectID);
}

void Xeno::Texture::Bind(const bool activeTexture, const uint32_t slot) const
{
    if (activeTexture)
        glActiveTexture(GL_TEXTURE0 + slot);

    glBindTexture(GL_TEXTURE_2D, mObjectID);
}

void Xeno::Texture::SetDataNew(void* data, TextureProperties props, const bool mipMap, const int32_t mipMapLevel)
{
    mProps = std::move(props);

    Bind(false);

    glTexImage2D(GL_TEXTURE_2D,
                 mipMapLevel,
                 mProps.mInternalFormat,
                 mProps.mWidth,
                 mProps.mHeight,
                 0,
                 mProps.mImageFormat,
                 mProps.mDataType,
                 data);

    if (mipMap)
        glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mProps.mFilterMax);
}

void Xeno::Texture::SetDataExisting(void* data, const int32_t mipMapLevel) const
{
    Bind(false);

    glTexSubImage2D(GL_TEXTURE_2D,
                    mipMapLevel,
                    0,
                    0,
                    mProps.mWidth,
                    mProps.mHeight,
                    mProps.mImageFormat,
                    mProps.mDataType,
                    data);
}

void Xeno::Texture::SetWrapS(const uint32_t mode)
{
    mProps.mWrapS = mode;
    Bind(false);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mProps.mWrapS);
}

void Xeno::Texture::SetWrapT(const uint32_t mode)
{
    mProps.mWrapT = mode;
    Bind(false);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mProps.mWrapS);
}

void Xeno::Texture::SetFilterMin(const uint32_t mode)
{
    mProps.mFilterMin = mode;
    Bind(false);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mProps.mFilterMin);
}

void Xeno::Texture::SetFilterMax(const uint32_t mode)
{
    mProps.mFilterMax = mode;
    Bind(false);
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

Xeno::Material::TextureMap Xeno::Texture::GetType() const
{
    return mProps.mType;
}

bool Xeno::Texture::InitSuccess() const
{
    return mInitSuccess;
}

bool Xeno::Texture::GenerateTextureFromFile(const bool mipMap, const int32_t mipMapLevel)
{
    XN_CORE_INFO("Generating texture: {0}", mProps.mPath);

    stbi_set_flip_vertically_on_load(1);

    int32_t width, height, channels;

    uint8_t* data = stbi_load(mProps.mPath.c_str(), &width, &height, &channels, 0);

    XN_CORE_ASSERT(data, "Failed to generate texture: " + mProps.mPath);

    switch (channels)
    {
    case 1:
        mProps.mInternalFormat = GL_RED;
        mProps.mImageFormat = GL_RED;
        break;
    case 3:
        mProps.mInternalFormat = GL_RGB;
        mProps.mImageFormat = GL_RGB;
        break;
    case 4:
        mProps.mInternalFormat = GL_RGBA;
        mProps.mImageFormat = GL_RGBA;
        break;
    default:
        break;
    }

    mProps.mWidth = width;
    mProps.mHeight = height;

    SetDataNew(data, mProps, mipMap, mipMapLevel);

    stbi_image_free(data);

    XN_CORE_INFO("Successfully generated texture.\n");

    return true;
}
