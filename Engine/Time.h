#pragma once

#include "Engine.h"

namespace arias
{
	class Time
	{
	private:
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
		static float mBulletTime;
		static float mOneSecond;

	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

	public:
		static __forceinline float DeltaTime() { return mDeltaTime; }
	};
}