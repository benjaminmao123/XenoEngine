#include "pch.h"
#include "Texture.h"

#include <stb/stb_image.h>

Xeno::Texture::Texture(uint32_t internalFormat, uint32_t imageFormat, 
                       uint32_t wrapS, uint32_t wrapT, 
                       uint32_t filterMin, uint32_t filterMax, 
                       bool mipMapping) :
    mInternalFormat(internalFormat), mImageFormat(imageFormat),
    mWrapS(wrapS), mWrapT(wrapT),
    mFilterMin(filterMin), mFilterMax(filterMax),
    mMipMapping(mipMapping)
{ }

Xeno::Texture::Texture(uint32_t width, uint32_t height, 
                       uint32_t internalFormat, uint32_t imageFormat, 
                       uint32_t wrapS, uint32_t wrapT, 
                       uint32_t filterMin, uint32_t filterMax, 
                       bool mipMapping) :
    Texture(mInternalFormat, mImageFormat, 
            mWrapS, mWrapT, 
            mFilterMin, mFilterMax, 
            mMipMapping)
{
    mWidth = width;
    mHeight = height;


}

Xeno::Texture::Texture(const std::string& path, 
                       uint32_t internalFormat, uint32_t imageFormat, 
                       uint32_t wrapS, uint32_t wrapT, 
                       uint32_t filterMin, uint32_t filterMax, 
                       bool mipMapping) :
    Texture(mInternalFormat, mImageFormat,
            mWrapS, mWrapT,
            mFilterMin, mFilterMax,
            mMipMapping)
{

}

Xeno::Texture::~Texture()
{
}

void Xeno::Texture::Bind(uint32_t slot) const
{
}

void Xeno::Texture::Unbind() const
{
}

void Xeno::Texture::LoadTextureFromFile(const std::string& path)
{
}
