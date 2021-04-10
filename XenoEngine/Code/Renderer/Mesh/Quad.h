#pragma once

#include "Core/Core.h"
#include "Renderer/Mesh/Mesh.h"

namespace Xeno
{
    struct XENO_API Quad final : Mesh
    {
        explicit Quad(Topology topology = Topology::TRIANGLES);
    };
}

