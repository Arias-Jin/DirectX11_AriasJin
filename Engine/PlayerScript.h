#pragma once
#include "Script.h"

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

		Vector3 mMousePos;
		Vector3 mPos;
		Vector3 mRot;

		float mMoveSpeed;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}