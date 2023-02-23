#pragma once
#include "BaseRenderer.h"

#include "Component.h"

#include "Material.h"
#include "Mesh.h"

namespace arias
{
	using namespace arias::graphics;

	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}