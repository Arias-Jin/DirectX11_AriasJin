#include "PlayScene.h"

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
#include "Animator.h"
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
#pragma region Player
		Player* playerObject = object::Instantiate<Player>(eLayerType::Player, this);
		SpriteRenderer* playerSprite = playerObject->AddComponent<SpriteRenderer>();
		Animator* playerAnimator = playerObject->AddComponent<Animator>();
		Collider2D* playerCollider = playerObject->AddComponent<Collider2D>();
		Transform* playerTransform = playerObject->AddComponent<Transform>();
		playerObject->AddComponent<PlayerScript>();
		
		std::shared_ptr<Mesh> playerMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> playerMaterial = ResourceManager::Find<Material>(L"PlayerMaterial");
		std::shared_ptr<Texture> playerTexture = ResourceManager::Load<Texture>(L"Player", L"Play\\Charater.png");
		
		playerSprite->SetMesh(playerMesh);
		playerSprite->SetMaterial(playerMaterial);

		playerAnimator->Create(L"Idle", playerTexture, Vector2(0.0f, 0.0f), Vector2(201.0f, 130.0f), Vector2::Zero, 20 , 0.05f);
		playerAnimator->Play(L"Idle", true);
		
		playerCollider->SetType(eColliderType::Circle);
		playerCollider->SetRadius(50.0f);
		
		playerTransform->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		playerTransform->SetScale(Vector3(100.0f, 100.0f, 1.0f));
#pragma endregion

#pragma region Enemy
		// Enemy* enemyObject = object::Instantiate<Enemy>(eLayerType::Enemy, this);
		// SpriteRenderer* enemySprite = enemyObject->AddComponent<SpriteRenderer>();
		// Collider2D* enemyCollider = enemyObject->AddComponent<Collider2D>();
		// Transform* enemyTransform = enemyObject->AddComponent<Transform>();
		// 
		// std::shared_ptr<Mesh> enemyMesh = ResourceManager::Find<Mesh>(L"RectMesh");
		// std::shared_ptr<Material> enemyMaterial = ResourceManager::Find<Material>(L"PlayerMaterial");
		// 
		// enemySprite->SetMesh(enemyMesh);
		// enemySprite->SetMaterial(enemyMaterial);
		// 
		// enemyCollider->SetType(eColliderType::Circle);
		// enemyCollider->SetRadius(100.0f);
		// 
		// // enemyTransform->SetParent(playerTransform);
		// enemyTransform->SetPosition(Vector3(250.0f, 0.0f, 10.0f));
		// enemyTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));
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

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);

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
		Scene::OnEnter();
		Initialize();
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}