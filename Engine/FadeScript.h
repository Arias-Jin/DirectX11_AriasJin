#pragma once
#include "Script.h"

namespace arias
{
	using namespace arias::math;

	class FadeScript : public Script
	{
	public:
		FadeScript();
		virtual ~FadeScript();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	private:
	};
}