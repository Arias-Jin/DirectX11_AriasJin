#include "SceneManager.h"

#include "MeshRenderer.h"
#include "Transform.h"
#include "PlayerScript.h"

#include "Renderer.h"

#include "Resources.h"
#include "Texture.h"

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

		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		Material* material = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		material->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMesh(mesh);
		mr->SetMaterial(material);

		PlayerScript* script = new PlayerScript();
		obj->AddComponent(script);

		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

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