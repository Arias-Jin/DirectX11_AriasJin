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
		static UINT ColliderNumber;
		UINT mID;

		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		float mRadius;

		bool mbTrigger;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

	public:
		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetRadius(float radius) { mRadius = radius; }

		bool IsTrigger() const { return mbTrigger; }

		UINT GetID() { return mID; }
		Vector3 GetPosition() { return mPosition; }
	};
}