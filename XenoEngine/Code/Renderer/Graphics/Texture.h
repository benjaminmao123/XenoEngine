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
        explicit Texture(std::string path,
                         uint32_t internalFormat = GL_RGB, 
                         uint32_t imageFormat = GL_RGB,
                         uint32_t wrapS = GL_REPEAT, 
                         uint32_t wrapT = GL_REPEAT,
                         uint32_t filterMin = GL_LINEAR, 
                         uint32_t filterMax = GL_LINEAR,
                         bool mipMapping = true,
                         int32_t mipMapLevel = 0);
        explicit Texture(uint32_t width, uint32_t height,
                         uint32_t internalFormat = GL_RGB,
                         uint32_t imageFormat = GL_RGB,
                         uint32_t wrapS = GL_REPEAT,
                         uint32_t wrapT = GL_REPEAT,
                         uint32_t filterMin = GL_LINEAR,
                         uint32_t filterMax = GL_LINEAR,
                         bool mipMapping = true,
                         int32_t mipMapLevel = 0,
                         int32_t numSamples = 1);
        ~Texture();
        Texture& operator=(const Texture& other) = delete;

        void Bind(uint32_t slot = 0) const;

        void SetData(void* data, uint32_t size) const;
        void SetWrapS(uint32_t mode);
        void SetWrapT(uint32_t mode);
        void SetFilterMin(uint32_t mode);
        void SetFilterMax(uint32_t mode);

        [[nodiscard]] uint32_t GetWidth() const;
        [[nodiscard]] uint32_t GetHeight() const;
        [[nodiscard]] uint32_t GetObjectID() const;
        [[nodiscard]] const std::string& GetPath() const;

    private:
        void GenerateTextureFromFile();

        std::string mPath;
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
        int32_t mMipMapLevel;
    };
}