#pragma once

#include "CommonInclude.h"

namespace arias
{
	class Time
	{
	private:
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
		static float mOneSecond;

	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

	public:
		static __forceinline float DeltaTime() { return mDeltaTime; }
	};
}