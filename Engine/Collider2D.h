#pragma once
#include "Component.h"

#include "Transform.h"

namespace arias
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

	private:
		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;

		bool mbTrigger;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
	};
}