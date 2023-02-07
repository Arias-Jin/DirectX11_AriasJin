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
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

	public:
		void SetPosition(Vector3 position) { mPosition = position; }
		Vector3 GetPosition() const { return mPosition; }

		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		Vector3 GetRotation() const { return mRotation; }

		void SetScale(Vector3 scale) { mScale = scale; }
		Vector3 GetScale() const { return mScale; }
	};
}