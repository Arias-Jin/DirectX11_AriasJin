#include "TitleScene.h"

#include "Camera.h"
#include "CollisionManager.h"
#include "Collider2D.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "CameraScript.h"
#include "FadeScript.h"
#include "GridScript.h"
#include "CrosshairScript.h"
#include "PlayerScript.h"
#include "Transform.h"

#include "Object.h"
#include "Player.h"
#include "Enemy.h"

#include "Input.h"

#include "Renderer.h"

#include "ResourceManager.h"
#include "Texture.h"

namespace arias
{
	TitleScene::TitleScene() :
		Scene(eSceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
#pragma region Main Camera
		GameObject* cameraObject = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComponent = cameraObject->AddComponent<Camera>();
		Transform* cameraTransform = cameraObject->AddComponent<Transform>();
		cameraObject->AddComponent<CameraScript>();

		mainCamera = cameraComponent;

		cameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComponent->TurnLayerMask(eLayerType::UI, false);

		cameraTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		
		object::DontDestroyOnLoad(cameraObject);
#pragma endregion

#pragma region UI Camera
		GameObject* uiCameraObject = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* uiCameraComponent = uiCameraObject->AddComponent<Camera>();
		Transform* uiCameraTransform = uiCameraObject->AddComponent<Transform>();
		uiCameraObject->AddComponent<CameraScript>();
		
		uiCameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		uiCameraComponent->TurnLayerMask(eLayerType::UI, true);
		uiCameraComponent->DisableLayerMasks();
		
		uiCameraTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		object::DontDestroyOnLoad(uiCameraObject);
#pragma endregion

#pragma region Crosshair UI
		GameObject* crosshairObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* crosshairRenderer = crosshairObject->AddComponent<SpriteRenderer>();
		Transform* crosshairTransform = crosshairObject->AddComponent<Transform>();
		crosshairObject->AddComponent<CrosshairScript>();
		
		std::shared_ptr<Mesh> crosshairMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> crosshairMaterial = ResourceManager::Find<Material>(L"CrosshairMaterial");
		
		crosshairRenderer->SetMesh(crosshairMesh);
		crosshairRenderer->SetMaterial(crosshairMaterial);
		
		crosshairTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		crosshairTransform->SetScale(Vector3(35.0f, 35.0f, 1.0f));
#pragma endregion

#pragma region Title Background
		GameObject* backgroundObject = object::Instantiate<GameObject>(eLayerType::Background, this);
		SpriteRenderer* backgroundRenderer = backgroundObject->AddComponent<SpriteRenderer>();
		Transform* backgroundTransform = backgroundObject->AddComponent<Transform>();
		
		std::shared_ptr<Mesh> backgroundMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> backgroundMaterial = ResourceManager::Find<Material>(L"BackgroundMaterial");
		
		backgroundRenderer->SetMesh(backgroundMesh);
		backgroundRenderer->SetMaterial(backgroundMaterial);
		
		backgroundTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		backgroundTransform->SetScale(Vector3(1600.0f, 900.0f, 1.0f));
#pragma endregion

#pragma region Play Button
		GameObject* playButtonObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* playButtonRenderer = playButtonObject->AddComponent<SpriteRenderer>();
		Transform* playButtonTransform = playButtonObject->AddComponent<Transform>();

		std::shared_ptr<Mesh> playButtonMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> playButtonMaterial = ResourceManager::Find<Material>(L"PlayButtonMaterial");

		playButtonRenderer->SetMesh(playButtonMesh);
		playButtonRenderer->SetMaterial(playButtonMaterial);

		playButtonTransform->SetPosition(Vector3(-400.0f, 0.0f, 0.0f));
		playButtonTransform->SetScale(Vector3(185.0f, 48.0f, 1.0f));
#pragma endregion

#pragma region Option Button
		GameObject* optionButtonObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* optionButtonRenderer = optionButtonObject->AddComponent<SpriteRenderer>();
		Transform* optionButtonTransform = optionButtonObject->AddComponent<Transform>();

		std::shared_ptr<Mesh> optionButtonMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> optionButtonMaterial = ResourceManager::Find<Material>(L"OptionButtonMaterial");

		optionButtonRenderer->SetMesh(optionButtonMesh);
		optionButtonRenderer->SetMaterial(optionButtonMaterial);

		optionButtonTransform->SetPosition(Vector3(-400.0f, -75.0f, 0.0f));
		optionButtonTransform->SetScale(Vector3(185.0f, 48.0f, 1.0f));
#pragma endregion

#pragma region Exit Button
		GameObject* exitButtonObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* exitButtonRenderer = exitButtonObject->AddComponent<SpriteRenderer>();
		Transform* exitButtonTransform = exitButtonObject->AddComponent<Transform>();

		std::shared_ptr<Mesh> exitButtonMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> exitButtonMaterial = ResourceManager::Find<Material>(L"ExitButtonMaterial");

		exitButtonRenderer->SetMesh(exitButtonMesh);
		exitButtonRenderer->SetMaterial(exitButtonMaterial);

		exitButtonTransform->SetPosition(Vector3(-400.0f, -150.0f, 0.0f));
		exitButtonTransform->SetScale(Vector3(185.0f, 48.0f, 1.0f));
#pragma endregion

#pragma region Fade
		// GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::None);
		// SpriteRenderer* fadeSprite = fadeObject->AddComponent<SpriteRenderer>();
		// Transform* fadeTransform = fadeObject->AddComponent<Transform>();
		// fadeObject->AddComponent<FadeScript>();
		// 
		// std::shared_ptr<Mesh> fadeMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		// std::shared_ptr<Material> fadeMaterial = ResourceManager::Find<Material>(L"FadeMaterial");
		// 
		// fadeSprite->SetMesh(fadeMesh);
		// fadeSprite->SetMaterial(fadeMaterial);
		// 
		// fadeTransform->SetPosition(Vector3(300.0f, 0.0f, 10.0f));
		// fadeTransform->SetScale(Vector3(100.0f, 100.0f, 1.0f));
#pragma endregion


		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
		Initialize();
	}

	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
}