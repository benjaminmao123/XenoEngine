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
        enum class Topology
        {
            TRIANGLES = GL_TRIANGLES
        };

        struct Vertex
        {
            glm::vec3 mPosition { 0.0f, 0.0f, 0.0f };
            glm::vec4 mColor { 0.0f, 0.0f, 0.0f, 1.0f };
            glm::vec2 mUV { 0.0f, 0.0f };
            glm::vec3 mNormal { 0.0f, 0.0f, 0.0f };
            glm::vec3 mTangent { 0.0f, 0.0f, 0.0f };
            glm::vec3 mBiTangent { 0.0f, 0.0f, 0.0f };
        };

        explicit Mesh(Topology topology);
        virtual ~Mesh() = default;

        Topology mTopology;
        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;
    };
}