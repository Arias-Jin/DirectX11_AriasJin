#pragma once
#include "..\Engine\GameObject.h"

namespace arias
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

	private:

	public:
		virtual void FixedUpdate() override;
	};
}