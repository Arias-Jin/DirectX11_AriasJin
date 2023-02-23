#pragma once
#include "Component.h"

#include "BaseRenderer.h"

#include "Material.h"
#include "Mesh.h"

namespace arias
{
	using namespace arias::graphics;

	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}