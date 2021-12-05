#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>
#include <vector>
#include <cstdint>
#include <string>

namespace Xeno
{
    class Texture;

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
        explicit Mesh(uint32_t topology,
                      std::vector<Vertex> vertices,
                      std::vector<uint32_t> indices);
        virtual ~Mesh() = default;

        glm::vec3 ComputeNormal(size_t index);
        void ComputeNormals();

        uint32_t mTopology;
        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;
    };
}