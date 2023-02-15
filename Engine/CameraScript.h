#pragma once
#include "Script.h"

namespace arias
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

	private:

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}