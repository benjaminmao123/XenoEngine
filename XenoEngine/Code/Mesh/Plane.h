#pragma once

#include "Core/Core.h"
#include "Mesh/Mesh.h"

namespace Xeno
{
    struct XENO_API Plane final : Mesh
    {
        explicit Plane(int32_t xSegments = 10, int32_t ySegments = 10, uint32_t topology = GL_TRIANGLE_STRIP);
    };
}