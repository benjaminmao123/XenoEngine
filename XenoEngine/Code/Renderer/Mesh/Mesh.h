#pragma once

#include "Core/Core.h"

#include <glad/glad.h>

namespace Xeno
{
    struct XENO_API Mesh
    {
        enum class Topology
        {
            TRIANGLES = GL_TRIANGLES
        };

        explicit Mesh(Topology topology);
        virtual ~Mesh() = 0;

        Topology mTopology;
    };
}
