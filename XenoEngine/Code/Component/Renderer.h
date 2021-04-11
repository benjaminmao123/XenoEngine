#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

namespace Xeno
{
    class XENO_API Renderer : public Component
    {
	public:
	    explicit Renderer(Entity* owner = nullptr);
		virtual ~Renderer() = 0;

	private:
		virtual void OnRender() const;

		friend class Entity;
    };
}