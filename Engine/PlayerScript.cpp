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
		mMoveSpeed(150.0f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		// Animator* animator = GetOwner()->GetComponent<Animator>();
		// animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		// animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		// animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		// animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);

		mTrans = GetOwner()->GetComponent<Transform>();
	}

	void PlayerScript::Update()
	{
#pragma region Player Position
		mPos = mTrans->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			mPos.x += mMoveSpeed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			mPos.x -= mMoveSpeed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			mPos.y += mMoveSpeed * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			mPos.y -= mMoveSpeed * Time::DeltaTime();
		}

		mTrans->SetPosition(mPos);
#pragma endregion
#pragma region Player Rotation
		mMousePos = Input::GetMouseWorldPosition();
		mRot = mTrans->GetRotation();

		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);

		mTrans->SetRotation(mRot);
#pragma endregion

		Animator* animator = GetOwner()->GetComponent<Animator>();
		
		// if (Input::GetKeyDown(eKeyCode::N_1))
		// {
		// 	animator->Play(L"MoveDown");
		// }
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
	
	void PlayerScript::Start()
	{
	}
	
	void PlayerScript::Action()
	{
	}
	
	void PlayerScript::End()
	{
	}
}