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
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }

		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
	};
}