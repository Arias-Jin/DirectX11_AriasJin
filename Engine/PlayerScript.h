#pragma once
#include "Script.h"

#include "Player.h"

namespace arias
{
	class Transform;

	using namespace arias::math;

	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

	private:
		Transform* mTrans;
		Vector2 mMousePos;
		Vector3 mPos;
		Vector3 mRot;

		bool bMove;
		float mMoveSpeed;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
	
	public:
		void KeyboardInput();
		void MouseInput();

	public:
	};
}