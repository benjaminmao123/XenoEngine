#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Mesh/Quad.h"

namespace Xeno
{
    class XENO_API Sprite final : public Component
    {
    public:
        explicit Sprite(Entity* owner = nullptr);

        [[nodiscard]] const Quad& GetQuad() const;

    private:
        Quad mQuad;
    };
}