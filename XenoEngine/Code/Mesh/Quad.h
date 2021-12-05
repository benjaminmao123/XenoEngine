#pragma once

#include "Core/Core.h"
#include "Mesh/Mesh.h"

#include <glad/glad.h>

namespace Xeno
{
    struct XENO_API Quad final : Mesh
    {
        explicit Quad(uint32_t topology = GL_TRIANGLES);
    };
}