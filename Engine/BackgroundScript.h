#pragma once
#include "Script.h"

namespace arias
{
	class Transform;

	using namespace arias::math;

	class BackgroundScript : public Script
	{
	public:
		BackgroundScript();
		~BackgroundScript();

	private:
		Transform* mTrans;

		Vector3 mPos;
		Vector3 mScale;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}