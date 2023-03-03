#include "TitleScene.h"

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
		GameObject* cameraObject = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComponent = cameraObject->AddComponent<Camera>();
		Transform* cameraTransform = cameraObject->AddComponent<Transform>();
		cameraObject->AddComponent<CameraScript>();

		cameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComponent->TurnLayerMask(eLayerType::UI, false);
		cameraComponent->RegisterCameraInRenderer();

		cameraTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
#pragma endregion

#pragma region UI Camera
		GameObject* uiCameraObject = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* uiCameraComponent = uiCameraObject->AddComponent<Camera>();
		Transform* uiCameraTransform = uiCameraObject->AddComponent<Transform>();
		uiCameraObject->AddComponent<CameraScript>();
		
		uiCameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		uiCameraComponent->TurnLayerMask(eLayerType::UI, true);
		uiCameraComponent->DisableLayerMasks();
		
		uiCameraTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
#pragma endregion

#pragma region Crosshair UI
		GameObject* crosshairObject = object::Instantiate<GameObject>(eLayerType::UI);
		SpriteRenderer* crosshairRenderer = crosshairObject->AddComponent<SpriteRenderer>();
		Transform* crosshairTransform = crosshairObject->AddComponent<Transform>();
		crosshairObject->AddComponent<CrosshairScript>();
		
		std::shared_ptr<Mesh> crosshairMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> crosshairMaterial = ResourceManager::Find<Material>(L"CrosshairMaterial");
		
		crosshairRenderer->SetMesh(crosshairMesh);
		crosshairRenderer->SetMaterial(crosshairMaterial);
		
		crosshairTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		crosshairTransform->SetScale(Vector3(25.0f, 25.0f, 1.0f));
#pragma endregion

#pragma region Grid Object
		GameObject* gridObject = object::Instantiate<GameObject>(eLayerType::Grid);
		MeshRenderer* gridRenderer = gridObject->AddComponent<MeshRenderer>();
		Transform* gridTransform = gridObject->AddComponent<Transform>();
		gridObject->AddComponent<GridScript>();
		
		std::shared_ptr<Mesh> gridMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gridMaterial = ResourceManager::Find<Material>(L"GridMaterial");
		
		gridRenderer->SetMesh(gridMesh);
		gridRenderer->SetMaterial(gridMaterial);
		
		gridTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
#pragma endregion

#pragma region Player
		GameObject* playerObject = object::Instantiate<GameObject>(eLayerType::Player);
		SpriteRenderer* playerSprite = playerObject->AddComponent<SpriteRenderer>();
		Transform* playerTransform = playerObject->AddComponent<Transform>();
		playerObject->AddComponent<PlayerScript>();

		std::shared_ptr<Mesh> playerMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> playerMaterial = ResourceManager::Find<Material>(L"PlayerMaterial");

		playerSprite->SetMesh(playerMesh);
		playerSprite->SetMaterial(playerMaterial);

		playerTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		playerTransform->SetScale(Vector3(100.0f, 100.0f, 1.0f));

		object::DontDestroyOnLoad(playerObject);
#pragma endregion

#pragma region Fade
		GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::None);
		SpriteRenderer* fadeSprite = fadeObject->AddComponent<SpriteRenderer>();
		Transform* fadeTransform = fadeObject->AddComponent<Transform>();
		fadeObject->AddComponent<FadeScript>();

		std::shared_ptr<Mesh> fadeMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> fadeMaterial = ResourceManager::Find<Material>(L"FadeMaterial");

		fadeSprite->SetMesh(fadeMesh);
		fadeSprite->SetMaterial(fadeMaterial);

		fadeTransform->SetPosition(Vector3(300.0f, 0.0f, 10.0f));
		fadeTransform->SetScale(Vector3(100.0f, 100.0f, 1.0f));
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
	}

	void TitleScene::OnExit()
	{
	}
}