#include "SceneManager.h"

#include "Transform.h"

#include "MeshRenderer.h"


namespace arias
{
	Scene* SceneManager::mPlayScene = nullptr;

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();

		tr->SetPosition(Vector3(0.2f, 0.2f, 0.2f));
		obj->AddComponent(tr);

		mPlayScene->AddGameObject(obj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
}