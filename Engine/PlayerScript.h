#pragma once
#include "Script.h"

namespace arias
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

	private:

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}