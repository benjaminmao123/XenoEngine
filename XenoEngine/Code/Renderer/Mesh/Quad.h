#pragma once

#include "Core/Core.h"
#include "Renderer/Mesh/Mesh.h"

#include <glm/glm.hpp>
#include <vector>

namespace Xeno
{
    struct XENO_API Quad final : Mesh
    {
        struct Vertex
        {
            glm::vec3 mPosition;
            glm::vec4 mColor;
            glm::vec2 mUVs;
            float mTexIndex;
        };

        explicit Quad(Topology topology);

        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;

        static inline const uint32_t sNumVertices = 4;
        static inline const uint32_t sNumIndices = 6;
    };
}

