#pragma once
#include "Script.h"

namespace arias
{
	class CrosshairScript : public Script
	{
	public:
		CrosshairScript();
		~CrosshairScript();

	private:
		float mWinWidthCenter;
		float mWinHeightCenter;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}

