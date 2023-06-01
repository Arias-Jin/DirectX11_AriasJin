#pragma once
#include "Component.h"

using namespace arias::math;

namespace arias
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

	private:
		Transform* mParent;
		Vector3 mForward;
		Vector3 mRight;
		Vector3 mUp;

		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Matrix mWorld;

		bool mInheritParentTransform;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

	public:
		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() const { return mParent; }

		void SetPosition(const Vector3 position) { mPosition = position; }
		void SetPositionX(const float positionX) { mPosition.x = positionX; }
		void SetPositionY(const float positionY) { mPosition.y = positionY; }
		void SetPositionZ(const float positionZ) { mPosition.z = positionZ; }
		void SetPositionXY(const Vector2& position) { mPosition.x = position.x; mPosition.y = position.y; }
		Vector3 GetPosition() const { return mPosition; }
		float GetPositionX() const { return mPosition.x; }
		float GetPositionY() const { return mPosition.y; }
		float GetPositionZ() const { return mPosition.z; }
		Vector2 GetPositionXY() const { return Vector2(mPosition.x, mPosition.y); }

		void SetRotation(const Vector3& rotation) { mRotation = rotation; }
		void SetRotationX(const float rotationX) { mRotation.x = rotationX; }
		void SetRotationY(const float rotationY) { mRotation.y = rotationY; }
		void SetRotationZ(const float rotationZ) { mRotation.z = rotationZ; }
		void SetRotationXY(const Vector2& rotation) { mRotation.x = rotation.x; mRotation.y = rotation.y; }
		Vector3 GetRotation() const { return mRotation; }
		float GetRotationX() const { return mRotation.x; }
		float GetRotationY() const { return mRotation.y; }
		float GetRotationZ() const { return mRotation.z; }
		Vector2 GetRotationXY() const { return Vector2(mRotation.x, mRotation.y); }

		void SetScale(const Vector3& scale) { mScale = scale; }
		void SetScaleX(const float scaleX) { mScale.x = scaleX; }
		void SetScaleY(const float scaleY) { mScale.y = scaleY; }
		void SetScaleZ(const float scaleZ) { mScale.z = scaleZ; }
		void SetScaleXY(const Vector2& scale) { mScale.x = scale.x; mScale.y = scale.y; }
		Vector3 GetScale() const { return mScale; }
		float GetScaleX() const { return mScale.x; }
		float GetScaleY() const { return mScale.y; }
		float GetScaleZ() const { return mScale.z; }
		Vector2 GetScaleXY() const { return Vector2(mScale.x, mScale.y); }

		Vector3 Forward() const { return mForward; }
		Vector3 Right() const { return mRight; }
		Vector3 Up() const { return mUp; }

		void AddPosition(const Vector3& position) { mPosition += position; }
		void AddPositionX(const float positionX) { mPosition.x += positionX; }
		void AddPositionY(const float positionY) { mPosition.y += positionY; }
		void AddPositionZ(const float positionZ) { mPosition.z += positionZ; }

		void AddRotation(const Vector3& rotation) { mRotation += rotation; }
		void AddRotationX(const float rotationX) { mRotation.x += rotationX; }
		void AddRotationY(const float rotationY) { mRotation.y += rotationY; }
		void AddRotationZ(const float rotationZ) { mRotation.z += rotationZ; }

		void AddScale(const Vector3& scale) { mScale += scale; }
		void AddScaleX(const float scaleX) { mScale.x += scaleX; }
		void AddScaleY(const float scaleY) { mScale.y += scaleY; }
		void AddScaleZ(const float scaleZ) { mScale.z += scaleZ; }

		void SetInheritParentTransform(bool inherit) { mInheritParentTransform = inherit; }
		
		Matrix& GetWorldMatrix() { return mWorld; }
	};
}