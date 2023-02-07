#include "MeshRenderer.h"

#include "Transform.h"

#include "GameObject.h"

namespace arias
{
	MeshRenderer::MeshRenderer() :
		Component(eComponentType::Mesh)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mShader->Binds();
		mMesh->BindBuffer();

		mMesh->Render();
	}
}