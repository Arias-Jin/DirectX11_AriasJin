#pragma once
#include "Entity.h"

#include "Layer.h"

namespace arias
{
	class Scene :public Entity
	{
	public:
		Scene();
		virtual ~Scene();

	private:
		std::vector<Layer> mLayers;

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}