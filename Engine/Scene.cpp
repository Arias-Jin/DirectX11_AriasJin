#include "Scene.h"

namespace arias
{
	Scene::Scene() :
		mLayers{}
	{
		mLayers.resize((UINT)eLayerType::End);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
	}
}