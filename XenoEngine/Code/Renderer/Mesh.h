#pragma once

#include "Core/Core.h"

#include <glad/glad.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Xeno
{
    class XENO_API Mesh
    {
    public:
        enum class Topology
        {
            TRIANGLES = GL_TRIANGLES
        };

        explicit Mesh(Topology topology);
        virtual ~Mesh() = 0;

        [[nodiscard]] Topology GetTopology() const;

    private:
        Topology mTopology;
        std::vector<glm::vec3> mPositions;
        std::vector<glm::vec4> mColors;
        std::vector<glm::vec2> mUVs;
    };
}
