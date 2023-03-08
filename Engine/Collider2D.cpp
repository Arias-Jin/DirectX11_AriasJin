#include "Collider2D.h"

#include "Renderer.h"

#include "GameObject.h"

namespace arias
{
	Collider2D::Collider2D() :
		Component(eComponentType::Collider),
		mType(eColliderType::None),
		mTransform(nullptr),
		mSize(Vector2::One),
		mCenter(Vector2::Zero),
		mbTrigger(false)
	{
	}
	
	Collider2D::~Collider2D()
	{
	}
	
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	
	void Collider2D::Update()
	{
	}
	
	void Collider2D::FixedUpdate()
	{
		Vector3 scale = mTransform->GetScale();
		scale *= Vector3(mSize.x, mSize.y, 1.0f);

		Vector3 rotation = mTransform->GetRotation();
		Vector3 position = mTransform->GetPosition();
		Vector3 colliderPos = position + Vector3(mCenter.x, mCenter.y, 0.0f);

		Matrix scaleMatrix = Matrix::CreateScale(scale);
		Matrix rotationMatrix;

		rotationMatrix = Matrix::CreateRotationX(rotation.x);
		rotationMatrix *= Matrix::CreateRotationY(rotation.y);
		rotationMatrix *= Matrix::CreateRotationZ(rotation.z);

		Matrix positionMatrix;

		positionMatrix.Translation(Vector3(colliderPos.x, colliderPos.y, colliderPos.z));

		Matrix worldMatrix = scaleMatrix * rotationMatrix * positionMatrix;
		DebugMesh meshAttribute = {};

		meshAttribute.position = Vector3(colliderPos.x, colliderPos.y, colliderPos.z);
		meshAttribute.radius = 1.0f;
		meshAttribute.rotation = rotation;
		meshAttribute.scale = scale;
		meshAttribute.type = mType;

		renderer::debugMeshes.push_back(meshAttribute);
	}
	
	void Collider2D::Render()
	{
	}
}