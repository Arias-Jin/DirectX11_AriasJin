#pragma once
#include "Component.h"

#include "Material.h"
#include "Mesh.h"

namespace arias
{
	class BaseRenderer : public Component
	{
	public:
		BaseRenderer(eComponentType type);
		virtual ~BaseRenderer();

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
		std::shared_ptr<Mesh> GetMesh() const { return mMesh; }

		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() const { return mMaterial; }
	};
}