#pragma once

#include "Core/Core.h"
#include "Renderer/Mesh/Mesh.h"

namespace Xeno
{
    struct XENO_API Cube final : Mesh
    {
        explicit Cube(Topology topology = Topology::TRIANGLES);
    };
}