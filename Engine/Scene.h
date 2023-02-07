#pragma once
#include "Entity.h"

#include "GameObject.h"

#include "Layer.h"

using namespace arias::enums;

namespace arias
{
	class Scene :public Entity
	{
	public:
		Scene();
		virtual ~Scene();

	private:
		std::vector<Layer> mLayers;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObj, const eLayerType type);
	};
}