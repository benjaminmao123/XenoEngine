#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

namespace Xeno
{
    class XENO_API RendererComponent : public Component
    {
	public:
	    explicit RendererComponent(Entity* owner = nullptr);
		virtual ~RendererComponent() = 0;

	private:
		virtual void Render() const;

		friend class Entity;
    };
}