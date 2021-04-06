#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Xeno
{
    class Texture;
    class Shader;

    class XENO_API ResourceManager : public NonCopyable
    {
    public:
        static void AddTexture(const std::shared_ptr<Texture>& texture);
        static std::shared_ptr<Texture> GetTexture(const std::string& path);
        static void AddShader(const std::shared_ptr<Shader>& shader);
        static std::shared_ptr<Shader> GetShader(const std::string& name);

    private:
        ResourceManager() = default;

        static std::unordered_map<std::string, std::shared_ptr<Texture>>& GetTextureCache();
        static std::unordered_map<std::string, std::shared_ptr<Shader>>& GetShaderCache();

        friend class Application;
    };
}