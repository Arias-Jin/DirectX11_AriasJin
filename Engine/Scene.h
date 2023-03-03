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
		Scene(eSceneType type);
		virtual ~Scene();

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();
		virtual void OnEnter();
		virtual void OnExit();

	public:
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		
		std::vector<GameObject*> GetDontDestroyGameObjects();

	public:
		eSceneType GetSceneType() const { return mType; }
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
	};
}