#include "SceneManager.h"

#include "Camera.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "PlayerScript.h"

#include "Renderer.h"

#include "ResourceManager.h"
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

		// Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);

		mPlayScene->AddGameObject(cameraObj, eLayerType::Camera);

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();

		tr->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Mesh> mesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = ResourceManager::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		material->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMesh(mesh.get());
		mr->SetMaterial(material.get());

		PlayerScript* script = new PlayerScript();
		obj->AddComponent(script);

		// std::shared_ptr<Texture> texture = ResourceManager::Load<Texture>(L"SmileTexture", L"Smile.png");
		std::shared_ptr<Texture> texture = ResourceManager::Load<Texture>(L"idle_flashlight_0", L"Top_Down_Survivor\\flashlight\\idle\\survivor-idle_flashlight_0.png");
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