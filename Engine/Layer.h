#pragma once

#include "GameObject.h"

namespace arias
{
	class Layer
	{
	public:
		Layer();
		~Layer();

	private:
		std::vector<GameObject*> mGameObjects;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}