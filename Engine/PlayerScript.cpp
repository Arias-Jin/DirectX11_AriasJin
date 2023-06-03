#include "PlayerScript.h"

#include "Animator.h"
#include "Transform.h"

#include "GameObject.h"

#include "Input.h"

#include "Time.h"

namespace arias
{
	PlayerScript::PlayerScript() :
		Script(),
		mTrans(nullptr),
		mMousePos{},
		mPos{},
		mRot{},
		bMove(false),
		mMoveSpeed(150.0f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		mTrans = GetOwner()->GetComponent<Transform>();
	}

	void PlayerScript::Update()
	{
		KeyboardInput();
		MouseInput();
	}

	void PlayerScript::FixedUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}
	
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::KeyboardInput()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());

		// Move
		mPos = mTrans->GetPosition();

		if (Input::GetKeyPress(eKeyCode::D))
		{
			player->ChangeState(ePlayerState::Move);
			mPos.x += mMoveSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyPress(eKeyCode::A))
		{
			player->ChangeState(ePlayerState::Move);
			mPos.x -= mMoveSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyPress(eKeyCode::W))
		{
			player->ChangeState(ePlayerState::Move);
			mPos.y += mMoveSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyPress(eKeyCode::S))
		{
			player->ChangeState(ePlayerState::Move);
			mPos.y -= mMoveSpeed * Time::DeltaTime();
		}

		mTrans->SetPosition(mPos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			player->ChangeState(ePlayerState::Idle);
		}

		// Change Weapon
		if (Input::GetKeyDown(eKeyCode::N_1))
		{
			player->ChangeWeapon(ePlayerWeapon::Knife);
		}
		if (Input::GetKeyDown(eKeyCode::N_2))
		{
			player->ChangeWeapon(ePlayerWeapon::Pistol);
		}
		if (Input::GetKeyDown(eKeyCode::N_3))
		{
			player->ChangeWeapon(ePlayerWeapon::Rifle);
		}
		if (Input::GetKeyDown(eKeyCode::N_4))
		{
			player->ChangeWeapon(ePlayerWeapon::Shotgun);
		}

		if (Input::GetKeyDown(eKeyCode::V))
		{
			player->ChangeState(ePlayerState::Melee);
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			player->ChangeState(ePlayerState::Reload);
		}
	}

	void PlayerScript::MouseInput()
	{
		mMousePos = Input::GetMouseWorldPosition();
		mRot = mTrans->GetRotation();

		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);

		mTrans->SetRotation(mRot);

		// if (Input::GetKeyDown())
	}
}