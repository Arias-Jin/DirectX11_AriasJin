#pragma once
#include "Script.h"

namespace arias
{
	class Camera;
	class Transform;

	using namespace arias::math;

	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

	private:
		Camera* mCamera;
		Transform* mTrans;
		
		Vector3 mPos;

		float mMoveSpeed;
		float mScale;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}