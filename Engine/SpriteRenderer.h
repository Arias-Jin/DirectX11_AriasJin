#pragma once
#include "Component.h"

#include "BaseRenderer.h"

#include "Material.h"
#include "Mesh.h"

using namespace arias::graphics;

namespace arias
{
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