#include "SceneManager.h"

#include "Camera.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "CameraScript.h"
#include "CrosshairScript.h"
#include "PlayerScript.h"
#include "Transform.h"

#include "Renderer.h"

#include "ResourceManager.h"
#include "Texture.h"

namespace arias
{
	Scene* SceneManager::mActiveScene = nullptr;

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();

		// Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);

		mActiveScene->AddGameObject(cameraObj, eLayerType::Camera);

		// Light Object
		GameObject* spriteObj = new GameObject();
		spriteObj->SetName(L"LIGHT");
		Transform* spriteTr = new Transform();
		spriteTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		spriteObj->AddComponent(spriteTr);

		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Mesh> mesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> spriteMaterial = ResourceManager::Find<Material>(L"SpriteMaterial");

		//Vector2 vec2(1.0f, 1.0f);
		//spriteMaterial->SetData(eGPUParam::Vector2, &vec2);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mActiveScene->AddGameObject(spriteObj, eLayerType::Player);

		//SMILE RECT
		GameObject* obj = new GameObject();
		obj->SetName(L"SMILE");
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Material> mateiral = ResourceManager::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		mActiveScene->AddGameObject(obj, eLayerType::Player);

		/*
		// Crosshair Object
		GameObject* crosshairObject = new GameObject();
		CrosshairScript* crosshairScript = new CrosshairScript();
		SpriteRenderer* crosshairSprite = new SpriteRenderer();
		Transform* crosshairTransform = new Transform();

		std::shared_ptr<Mesh> crosshairMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> crosshairMaterial = ResourceManager::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Texture> crosshairTexture = ResourceManager::Load<Texture>(L"CrosshairTexture", L"Crosshair.png");

		crosshairObject->AddComponent(crosshairScript);
		crosshairObject->AddComponent(crosshairSprite);
		crosshairObject->AddComponent(crosshairTransform);

		crosshairMaterial->SetTexture(crosshairTexture);

		crosshairSprite->SetMesh(crosshairMesh);
		crosshairSprite->SetMaterial(crosshairMaterial);

		crosshairTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		crosshairTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		mActiveScene->AddGameObject(crosshairObject, eLayerType::MousePointer);
		*/

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}