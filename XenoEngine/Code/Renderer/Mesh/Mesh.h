#pragma once

#include "Core/Core.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

namespace Xeno
{
    struct XENO_API Mesh
    {
        struct Vertex
        {
            glm::vec3 mPosition { 0.0f, 0.0f, 0.0f };
            glm::vec4 mColor { 0.0f, 0.0f, 0.0f, 1.0f };
            glm::vec2 mUV { 0.0f, 0.0f };
            glm::vec3 mNormal { 0.0f, 0.0f, 0.0f };
            glm::vec3 mTangent { 0.0f, 0.0f, 0.0f };
            glm::vec3 mBitangent { 0.0f, 0.0f, 0.0f };
        };

        explicit Mesh(uint32_t topology);
        virtual ~Mesh() = default;

        uint32_t mTopology;
        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;
    };
}