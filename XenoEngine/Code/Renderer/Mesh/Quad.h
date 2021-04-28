#pragma once

#include "Core/Core.h"
#include "Renderer/Mesh/Mesh.h"
#include "Utility/Graph.h"

namespace Xeno
{
    struct XENO_API Quad final : Mesh
    {
        explicit Quad(uint32_t topology = GL_TRIANGLES);
    };
}