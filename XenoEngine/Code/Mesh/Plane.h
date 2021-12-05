#pragma once

#include "Core/Core.h"
#include "Mesh/Mesh.h"

#include <glad/glad.h>

namespace Xeno
{
    struct XENO_API Plane final : Mesh
    {
        explicit Plane(int32_t xSegments = 11, int32_t ySegments = 11, uint32_t topology = GL_TRIANGLE_STRIP);
    };
}