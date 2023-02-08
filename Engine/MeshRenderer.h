#pragma once
#include "Component.h"

#include "Mesh.h"
#include "Material.h"

using namespace arias::graphics;

namespace arias
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

	private:
		Mesh* mMesh;
		Material* mMaterial;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void SetMesh(Mesh* mesh) { mMesh = mesh; }

		void SetMaterial(Material* material) { mMaterial = material; }
	};
}