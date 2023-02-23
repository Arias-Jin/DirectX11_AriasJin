#pragma once
#include "Script.h"

namespace arias
{
	class GameObject;
	class Transform;
	class Camera;

	using namespace arias::math;

	class GridScript : public Script
	{
	public:
		GridScript();
		virtual ~GridScript();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		GameObject* mObject;

		Transform* mTrans;
		Camera* mCamera;

		Vector2 mWinResolution;
		Vector3 mCameraPos;
		Vector4 mPos;

		float mScale;

	public:
		void SetCamera(Camera* camera) { mCamera = camera; }
	};
}