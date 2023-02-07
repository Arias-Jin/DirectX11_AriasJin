#include "SceneManager.h"

#include "MeshRenderer.h"
#include "Transform.h"

#include "Renderer.h"

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

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		mr->SetShader(renderer::shader);
		mr->SetMesh(renderer::mesh);

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