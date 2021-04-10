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
        static bool AddTexture(const std::shared_ptr<Texture>& texture);
        static Texture* GetTexture(const std::string& path);
        static bool AddShader(const std::shared_ptr<Shader>& shader);
        static Shader* GetShader(const std::string& name);

    private:
        ResourceManager() = default;

        static inline std::unordered_map<std::string, std::shared_ptr<Texture>> sTextureCache;
        static inline std::unordered_map<std::string, std::shared_ptr<Shader>> sShaderCache;

        friend class Application;
    };
}