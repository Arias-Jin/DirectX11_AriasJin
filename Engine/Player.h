#pragma once
#include "GameObject.h"

namespace arias
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

	private:

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}