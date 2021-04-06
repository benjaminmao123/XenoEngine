#pragma once

#include "Core/Core.h"
#include "Renderer/Mesh.h"

namespace Xeno
{
    class XENO_API Quad : public Mesh
    {
    public:
        Quad(Topology topology);
        ~Quad() override;

    private:

    };
}

