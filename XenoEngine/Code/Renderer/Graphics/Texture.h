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
        enum class TextureFormat
        {
            RGB = GL_RGB,
            RGBA = GL_RGBA
        };

        struct TextureProperties
        {
            std::string mPath;
            uint32_t mWidth = 1;
            uint32_t mHeight = 1;
            TextureFormat mInternalFormat = TextureFormat::RGBA;
            TextureFormat mImageFormat = TextureFormat::RGBA;
            uint32_t mDataType = GL_UNSIGNED_BYTE;
            uint32_t mWrapS = GL_REPEAT;
            uint32_t mWrapT = GL_REPEAT;
            uint32_t mFilterMin = GL_LINEAR;
            uint32_t mFilterMax = GL_LINEAR;
        };

        explicit Texture(TextureProperties props, int32_t mipMapLevel = 0);
        explicit Texture(void* data, TextureProperties props, int32_t mipMapLevel = 0);
        explicit Texture(TextureProperties props, int32_t numSamples, bool fixed);
        ~Texture();
        Texture& operator=(const Texture& other) = delete;

        void Bind(uint32_t slot = 0) const;

        void SetDataNew(void* data, TextureProperties props, int32_t mipMapLevel = 0);
        void SetDataExisting(void* data, int32_t mipMapLevel = 0) const;

        void SetWrapS(uint32_t mode);
        void SetWrapT(uint32_t mode);
        void SetFilterMin(uint32_t mode);
        void SetFilterMax(uint32_t mode);

        [[nodiscard]] uint32_t GetWidth() const;
        [[nodiscard]] uint32_t GetHeight() const;
        [[nodiscard]] uint32_t GetObjectID() const;
        [[nodiscard]] const std::string& GetPath() const;

        [[nodiscard]] bool InitSuccess() const;

    private:
        bool GenerateTextureFromFile(int32_t mipMapLevel);

        uint32_t mObjectID = 0;
        TextureProperties mProps;
        bool mInitSuccess = true;
    };
}