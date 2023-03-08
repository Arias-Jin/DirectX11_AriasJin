#include "PlayScene.h"

#include "Camera.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "CameraScript.h"
#include "FadeScript.h"
#include "GridScript.h"
#include "CrosshairScript.h"
#include "PlayerScript.h"
#include "Transform.h"

#include "Object.h"

#include "Input.h"

#include "Renderer.h"

#include "ResourceManager.h"
#include "Texture.h"

namespace arias
{
	PlayScene::PlayScene() :
		Scene(eSceneType::Play)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
#pragma region Main Camera
		GameObject* cameraObject = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComponent = cameraObject->AddComponent<Camera>();
		Transform* cameraTransform = cameraObject->AddComponent<Transform>();
		cameraObject->AddComponent<CameraScript>();
		
		cameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComponent->TurnLayerMask(eLayerType::UI, false);

		cameraTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
#pragma endregion

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
	}

	void PlayScene::OnExit()
	{
	}
}