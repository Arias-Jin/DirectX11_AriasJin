#include "SceneManager.h"

#include "Camera.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "CameraScript.h"
#include "GridScript.h"
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

#pragma region UI Camera
		GameObject* uiCameraObject = new GameObject();
		Camera* uiCameraComponent = new Camera();
		CameraScript* uiCameraScript = new CameraScript();
		Transform* uiCameraTransform = new Transform();

		uiCameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		uiCameraComponent->TurnLayerMask(eLayerType::UI, true);
		uiCameraComponent->DisableLayerMasks();

		uiCameraTransform->SetPosition(Vector3(0.0f, 0.0f, 100.0f));

		uiCameraObject->AddComponent(uiCameraComponent);
		uiCameraObject->AddComponent(uiCameraScript);
		uiCameraObject->AddComponent(uiCameraTransform);

		mActiveScene->AddGameObject(uiCameraObject, eLayerType::Camera);
#pragma endregion
#pragma region Crosshair UI
		GameObject* crosshairObject = new GameObject();
		SpriteRenderer* crosshairRenderer = new SpriteRenderer();
		CrosshairScript* crosshairScript = new CrosshairScript();
		Transform* crosshairTransform = new Transform();

		std::shared_ptr<Mesh> crosshairMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> crosshairMaterial = ResourceManager::Find<Material>(L"CrosshairMaterial");

		crosshairRenderer->SetMesh(crosshairMesh);
		crosshairRenderer->SetMaterial(crosshairMaterial);

		crosshairTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		crosshairTransform->SetScale(Vector3(0.25f, 0.25f, 1.0f));

		crosshairObject->AddComponent(crosshairRenderer);
		crosshairObject->AddComponent(crosshairScript);
		crosshairObject->AddComponent(crosshairTransform);

		mActiveScene->AddGameObject(crosshairObject, eLayerType::UI);
#pragma endregion
#pragma region Grid Object
		GameObject* gridObject = new GameObject();
		MeshRenderer* gridRenderer = new MeshRenderer();
		GridScript* gridScript = new GridScript();
		Transform* gridTransform = new Transform();

		std::shared_ptr<Mesh> gridMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> gridMaterial = ResourceManager::Find<Material>(L"GridMaterial");

		gridRenderer->SetMesh(gridMesh);
		gridRenderer->SetMaterial(gridMaterial);

		gridObject->AddComponent(gridRenderer);
		gridObject->AddComponent(gridScript);
		gridObject->AddComponent(gridTransform);

		mActiveScene->AddGameObject(gridObject, eLayerType::Grid);
#pragma endregion
#pragma region Main Camera
		GameObject* cameraObject = new GameObject();
		Camera* cameraComponent = new Camera();
		CameraScript* cameraScript = new CameraScript();
		Transform* cameraTransform = new Transform();
		
		cameraComponent->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComponent->TurnLayerMask(eLayerType::UI, false);
		cameraComponent->RegisterCameraInRenderer();
		
		cameraTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		cameraObject->AddComponent(cameraComponent);
		cameraObject->AddComponent(cameraScript);
		cameraObject->AddComponent(cameraTransform);
		
		mActiveScene->AddGameObject(cameraObject, eLayerType::Camera);
#pragma endregion
#pragma region Player
		GameObject* playerObject = new GameObject();
		SpriteRenderer* playerSprite = new SpriteRenderer();
		PlayerScript* playerScript = new PlayerScript();
		Transform* playerTransform = new Transform();

		std::shared_ptr<Mesh> playerMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> playerMaterial = ResourceManager::Find<Material>(L"PlayerMaterial");

		playerSprite->SetMesh(playerMesh);
		playerSprite->SetMaterial(playerMaterial);

		playerTransform->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		playerTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		playerObject->AddComponent(playerSprite);
		playerObject->AddComponent(playerScript);
		playerObject->AddComponent(playerTransform);

		mActiveScene->AddGameObject(playerObject, eLayerType::Player);
#pragma endregion

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