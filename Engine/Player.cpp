#include "Player.h"

#include "Animator.h"
#include "Collider2D.h"
#include "MeshRenderer.h"
#include "PlayerScript.h"
#include "Transform.h"

#include "ResourceManager.h"

#include "Input.h"

namespace arias
{
	Player::Player() :
		GameObject(),
		mPlayerState(ePlayerState::End),
		mPlayerWeapon(ePlayerWeapon::Knife),
		mWeaponName{},
		mAnimator(nullptr),
		mCollider2D(nullptr),
		mMeshRenderer(nullptr),
		mPlayerScript(nullptr),
		mTransform(nullptr),
		isMeleeAnimation(false),
		isReloadAnimation(false)
	{
		mAnimator = AddComponent<Animator>();
		mCollider2D = AddComponent<Collider2D>();
		mMeshRenderer = AddComponent<MeshRenderer>();
		mPlayerScript = AddComponent<PlayerScript>();
		mTransform = AddComponent<Transform>();

		std::shared_ptr<Mesh> mesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = ResourceManager::Find<Material>(L"PlayerMaterial");

		mMeshRenderer->SetMesh(mesh);
		mMeshRenderer->SetMaterial(material);

		CreateAnimation();

		mAnimator->Play(L"PlayerKnifeIdle", true);

		mCollider2D->SetType(eColliderType::Circle);
		mCollider2D->SetRadius(40.0f);

		mTransform->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		mTransform->SetScale(Vector3(150.0f, 150.0f, 1.0f));
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		mAnimator->GetStartEvent(L"PlayerKnifeMelee") = std::bind(&Player::Melee, this);
		mAnimator->GetStartEvent(L"PlayerPistolMelee") = std::bind(&Player::Melee, this);
		mAnimator->GetStartEvent(L"PlayerRifleMelee") = std::bind(&Player::Melee, this);
		mAnimator->GetStartEvent(L"PlayerShotgunMelee") = std::bind(&Player::Melee, this);
		mAnimator->GetCompleteEvent(L"PlayerKnifeMelee") = std::bind(&Player::CompleteMeleeAnimation, this);
		mAnimator->GetCompleteEvent(L"PlayerPistolMelee") = std::bind(&Player::CompleteMeleeAnimation, this);
		mAnimator->GetCompleteEvent(L"PlayerRifleMelee") = std::bind(&Player::CompleteMeleeAnimation, this);
		mAnimator->GetCompleteEvent(L"PlayerShotgunMelee") = std::bind(&Player::CompleteMeleeAnimation, this);
		mAnimator->GetEndEvent(L"PlayerKnifeMelee") = std::bind(&Player::EndMeleeAnimation, this);
		mAnimator->GetEndEvent(L"PlayerPistolMelee") = std::bind(&Player::EndMeleeAnimation, this);
		mAnimator->GetEndEvent(L"PlayerRifleMelee") = std::bind(&Player::EndMeleeAnimation, this);
		mAnimator->GetEndEvent(L"PlayerShotgunMelee") = std::bind(&Player::EndMeleeAnimation, this);

		mAnimator->GetStartEvent(L"PlayerPistolReload") = std::bind(&Player::Reload, this);
		mAnimator->GetStartEvent(L"PlayerRifleReload") = std::bind(&Player::Reload, this);
		mAnimator->GetStartEvent(L"PlayerShotgunReload") = std::bind(&Player::Reload, this);
		mAnimator->GetCompleteEvent(L"PlayerPistolReload") = std::bind(&Player::CompleteReloadAnimation, this);
		mAnimator->GetCompleteEvent(L"PlayerRifleReload") = std::bind(&Player::CompleteReloadAnimation, this);
		mAnimator->GetCompleteEvent(L"PlayerShotgunReload") = std::bind(&Player::CompleteReloadAnimation, this);
		mAnimator->GetEndEvent(L"PlayerPistolReload") = std::bind(&Player::EndReloadAnimation, this);
		mAnimator->GetEndEvent(L"PlayerRifleReload") = std::bind(&Player::EndReloadAnimation, this);
		mAnimator->GetEndEvent(L"PlayerShotgunReload") = std::bind(&Player::EndReloadAnimation, this);

		GameObject::Initialize();
	}

	void Player::CreateAnimation()
	{
		std::shared_ptr<Texture> texture = ResourceManager::Find<Texture>(L"PlayerTexture");

		mAnimator->Create(L"PlayerPistolIdle", texture, Vector2(0.0f, 0.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerKnifeIdle", texture, Vector2(400.0f, 400.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerRifleIdle", texture, Vector2(800.0f, 800.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerShotgunIdle", texture, Vector2(1200.0f, 1200.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		
		mAnimator->Create(L"PlayerPistolMelee", texture, Vector2(1600.0f, 1600.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 16, 0.05f);
		mAnimator->Create(L"PlayerKnifeMelee", texture, Vector2(0.0f, 2000.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 16, 0.05f);
		mAnimator->Create(L"PlayerRifleMelee", texture, Vector2(6400.0f, 2000.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 16, 0.05f);
		mAnimator->Create(L"PlayerShotgunMelee", texture, Vector2(4800.0f, 2400.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 16, 0.05f);
		
		mAnimator->Create(L"PlayerPistolMove", texture, Vector2(3200.0f, 2800.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerKnifeMove", texture, Vector2(3600.0f, 3200.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerRifleMove", texture, Vector2(4400.0f, 3600.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerShotgunMove", texture, Vector2(4400.0f, 4000.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		
		mAnimator->Create(L"PlayerPistolReload", texture, Vector2(4800.0f, 4400.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 16, 0.05f);
		mAnimator->Create(L"PlayerRifleReload", texture, Vector2(3200.0f, 4800.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		mAnimator->Create(L"PlayerShotgunReload", texture, Vector2(3600.0f, 5200.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 21, 0.05f);
		
		mAnimator->Create(L"PlayerPistolShoot", texture, Vector2(4000.0f, 5600.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"PlayerRifleShoot", texture, Vector2(5600.0f, 5600.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"PlayerShotgunShoot", texture, Vector2(7200.0f, 5600.0f), Vector2(400.0f, 400.0f), Vector2::Zero, 4, 0.1f);
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::FixedUpdate()
	{

		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

	void Player::ChangeState(ePlayerState playerState)
	{
		if (mPlayerState == playerState)
		{
			return;
		}
		
		mPlayerState = playerState;

		switch (playerState)
		{
		case ePlayerState::Idle:
			Idle();
			break;
		case ePlayerState::Melee:
			Melee();
			break;
		case ePlayerState::Move:
			Move();
			break;
		case ePlayerState::Reload:
			if (mPlayerWeapon == ePlayerWeapon::Knife)
			{
				ChangeState(ePlayerState::Idle);
				break;
			}
			Reload();
			break;
		case ePlayerState::Shoot:
			Shoot();
			break;
		case ePlayerState::End:
		default:
			break;
		}
	}

	void Player::ChangeWeapon(ePlayerWeapon playerWeapon)
	{
		if (mPlayerWeapon == playerWeapon)
		{
			return;
		}

		mPlayerWeapon = playerWeapon;
		
		Idle();
	}

	void Player::Idle()
	{
		switch (mPlayerWeapon)
		{
		case ePlayerWeapon::Knife:
			mAnimator->Play(L"PlayerKnifeIdle");
			break;
		case ePlayerWeapon::Pistol:
			mAnimator->Play(L"PlayerPistolIdle");
			break;
		case ePlayerWeapon::Rifle:
			mAnimator->Play(L"PlayerRifleIdle");
			break;
		case ePlayerWeapon::Shotgun:
			mAnimator->Play(L"PlayerShotgunIdle");
			break;
		case ePlayerWeapon::End:
		default:
			break;
		}
	}

	void Player::Melee()
	{
		if (isMeleeAnimation)
		{
			return;
		}

		isMeleeAnimation = true;

		switch (mPlayerWeapon)
		{
		case ePlayerWeapon::Knife:
			mAnimator->Play(L"PlayerKnifeMelee", false);
			break;
		case ePlayerWeapon::Pistol:
			mAnimator->Play(L"PlayerPistolMelee", false);
			break;
		case ePlayerWeapon::Rifle:
			mAnimator->Play(L"PlayerRifleMelee", false);
			break;
		case ePlayerWeapon::Shotgun:
			mAnimator->Play(L"PlayerShotgunMelee", false);
			break;
		case ePlayerWeapon::End:
		default:
			break;
		}
	}

	void Player::Move()
	{
		if (isMeleeAnimation || isReloadAnimation)
		{
			return;
		}

		switch (mPlayerWeapon)
		{
		case ePlayerWeapon::Knife:
			mAnimator->Play(L"PlayerKnifeMove");
			break;
		case ePlayerWeapon::Pistol:
			mAnimator->Play(L"PlayerPistolMove");
			break;
		case ePlayerWeapon::Rifle:
			mAnimator->Play(L"PlayerRifleMove");
			break;
		case ePlayerWeapon::Shotgun:
			mAnimator->Play(L"PlayerShotgunMove");
			break;
		case ePlayerWeapon::End:
		default:
			break;
		}
	}

	void Player::Reload()
	{
		if (isReloadAnimation)
		{
			return;
		}

		isReloadAnimation = true;

		switch (mPlayerWeapon)
		{
		case ePlayerWeapon::Pistol:
			mAnimator->Play(L"PlayerPistolReload", false);
			break;
		case ePlayerWeapon::Rifle:
			mAnimator->Play(L"PlayerRifleReload", false);
			break;
		case ePlayerWeapon::Shotgun:
			mAnimator->Play(L"PlayerShotgunReload", false);
			break;
		case ePlayerWeapon::End:
		default:
			break;
		}
	}

	void Player::Shoot()
	{
		switch (mPlayerWeapon)
		{
		case ePlayerWeapon::Knife:
			mAnimator->Play(L"PlayerKnifeMelee", false);
			break;
		case ePlayerWeapon::Pistol:
			mAnimator->Play(L"PlayerPistolShoot", false);
			break;
		case ePlayerWeapon::Rifle:
			mAnimator->Play(L"PlayerRifleShoot", false);
			break;
		case ePlayerWeapon::Shotgun:
			mAnimator->Play(L"PlayerShotgunShoot", false);
			break;
		case ePlayerWeapon::End:
		default:
			break;
		}
	}

	void Player::CompleteMeleeAnimation()
	{
		ChangeState(ePlayerState::Idle);
		isMeleeAnimation = false;
	}

	void Player::EndMeleeAnimation()
	{
		ChangeState(ePlayerState::Idle);
		isMeleeAnimation = false;
	}

	void Player::CompleteReloadAnimation()
	{
		ChangeState(ePlayerState::Idle);
		isReloadAnimation = false;
	}

	void Player::EndReloadAnimation()
	{
		ChangeState(ePlayerState::Idle);
		isReloadAnimation = false;
	}
}