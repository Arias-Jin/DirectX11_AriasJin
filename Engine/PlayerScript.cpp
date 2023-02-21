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
		mPos{},
		mRot{}
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		mTrans = GetOwner()->GetComponent<Transform>();

		mPos = mTrans->GetPosition();
		
		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			mPos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			mPos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			mPos.y += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			mPos.y -= 3.0f * Time::DeltaTime();
		}
		
		mTrans->SetPosition(mPos);
	}

	void PlayerScript::Render()
	{
	}
}