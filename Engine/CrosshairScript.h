#pragma once
#include "Script.h"

namespace arias
{
	class Transform;

	using namespace arias::math;

	class CrosshairScript : public Script
	{
	public:
		CrosshairScript();
		~CrosshairScript();

	private:
		float mWinWidthCenter;
		float mWinHeightCenter;

		POINT mMousePos;
		Transform* mTrans;
		Vector3 mPos;
		Vector3 mRot;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}

