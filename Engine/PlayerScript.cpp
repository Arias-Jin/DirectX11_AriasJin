#include "PlayerScript.h"

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
		mMoveSpeed(3.0f)
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
		mMousePos = Input::GetMousePosition();
		mRot = mTrans->GetRotation();

		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);

		mTrans->SetRotation(mRot);
#pragma endregion
	}

	void PlayerScript::Render()
	{
	}
}