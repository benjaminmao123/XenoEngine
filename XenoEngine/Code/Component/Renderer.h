#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Material/Material.h"

namespace Xeno
{
    class XENO_API Renderer : public Component
    {
	public:
	    explicit Renderer(Entity* owner = nullptr);
		virtual ~Renderer() = 0;

		void SetMaterial(const Material& material);
		[[nodiscard]] const Material& GetMaterial() const;
		[[nodiscard]] Material& GetMaterial();

	private:
		virtual void OnRender() const;

		Material mMaterial;

		friend class Entity;
    };
}