#pragma once
#include "GameObject.h"

namespace arias
{
	class Enemy : public GameObject
	{
	public:
		Enemy();
		virtual ~Enemy();

	private:

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}