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

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

	public:
		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() const { return mParent; }

		void SetPosition(Vector3 position) { mPosition = position; }
		Vector3 GetPosition() const { return mPosition; }

		void SetRotation(Vector3 degree) { mRotation = degree; }
		Vector3 GetRotation() const { return mRotation; }

		void SetScale(Vector3 scale) { mScale = scale; }
		Vector3 GetScale() const { return mScale; }

		Matrix& GetWorldMatrix() { return mWorld; }

		Vector3 Forward() const { return mForward; }
		Vector3 Right() const { return mRight; }
		Vector3 Up() const { return mUp; }
	};
}