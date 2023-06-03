#pragma once
#include "GameObject.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

namespace arias
{
	class Animator;
	class Collider2D;
	class MeshRenderer;
	class PlayerScript;
	class Transform;

	enum class ePlayerState
	{
		Idle,
		Melee,
		Move,
		Reload,
		Shoot,
		End,
	};

	enum class ePlayerWeapon
	{
		Knife,
		Pistol,
		Rifle,
		Shotgun,
		End,
	};

	struct WeaponName
	{
		std::wstring weaponIdleAnim;
		std::wstring weaponMeleeAnim;
		std::wstring weaponMoveAnim;
		std::wstring weaponReloadAnim;
		std::wstring weaponShootAnim;
	};

	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

	private:
		ePlayerState mPlayerState;
		ePlayerWeapon mPlayerWeapon;
		std::vector<WeaponName*> mWeaponName;

		Animator* mAnimator;
		Collider2D* mCollider2D;
		MeshRenderer* mMeshRenderer;
		PlayerScript* mPlayerScript;
		Transform* mTransform;

		bool isMeleeAnimation;
		bool isReloadAnimation;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void ChangeState(ePlayerState playerState);
		void ChangeWeapon(ePlayerWeapon playerWeapon);

		void Idle();
		void Melee();
		void Move();
		void Reload();
		void Shoot();

		void CreateAnimation();

		void CompleteMeleeAnimation();
		void EndMeleeAnimation();

		void CompleteReloadAnimation();
		void EndReloadAnimation();

	public:
		void SetPlayerWeapon(const ePlayerWeapon& playerWeapon) { mPlayerWeapon = playerWeapon; }
		ePlayerWeapon GetPlayerWeapon() const { return mPlayerWeapon; }

	};
}