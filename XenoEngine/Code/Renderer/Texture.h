#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <string>
#include <glad/glad.h>

namespace Xeno
{
    class XENO_API Texture
    {
    public:
        explicit Texture(uint32_t internalFormat = GL_RGB, 
                         uint32_t imageFormat = GL_RGB,
                         uint32_t wrapS = GL_REPEAT, 
                         uint32_t wrapT = GL_REPEAT,
                         uint32_t filterMin = GL_LINEAR, 
                         uint32_t filterMax = GL_LINEAR,
                         bool mipMapping = true);
        explicit Texture(uint32_t width, uint32_t height,
                         uint32_t internalFormat = GL_RGB, 
                         uint32_t imageFormat = GL_RGB,
                         uint32_t wrapS = GL_REPEAT, 
                         uint32_t wrapT = GL_REPEAT,
                         uint32_t filterMin = GL_LINEAR, 
                         uint32_t filterMax = GL_LINEAR,
                         bool mipMapping = true);
        explicit Texture(const std::string& path,
                         uint32_t internalFormat = GL_RGB, 
                         uint32_t imageFormat = GL_RGB,
                         uint32_t wrapS = GL_REPEAT, 
                         uint32_t wrapT = GL_REPEAT,
                         uint32_t filterMin = GL_LINEAR, 
                         uint32_t filterMax = GL_LINEAR,
                         bool mipMapping = true);
        ~Texture();

        void Bind(uint32_t slot) const;
        void Unbind() const;

        void LoadTextureFromFile(const std::string& path);

    private:
        uint32_t mObjectID;
        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mInternalFormat;
        uint32_t mImageFormat;
        uint32_t mWrapS;
        uint32_t mWrapT;
        uint32_t mFilterMin;
        uint32_t mFilterMax;
        bool mMipMapping;
    };
}