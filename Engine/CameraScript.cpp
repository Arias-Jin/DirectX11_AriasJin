#include "CameraScript.h"

#include "Camera.h"
#include "Transform.h"

#include "GameObject.h"

#include "Input.h"

#include "Time.h"

namespace arias
{
	CameraScript::CameraScript() :
		Script(),
		mCamera(nullptr),
		mTrans(nullptr),
		mPos{},
		mMoveSpeed(100.0f),
		mScale(1.0f)
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
		mTrans = GetOwner()->GetComponent<Transform>();
		mCamera = GetOwner()->GetComponent<Camera>();
	}
	
	void CameraScript::Update()
	{
		mPos = mTrans->GetPosition();

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			mPos += mMoveSpeed * mTrans->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			mPos += mMoveSpeed * -mTrans->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			mPos += mMoveSpeed * mTrans->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			mPos += mMoveSpeed * -mTrans->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::NUM_8) == eKeyState::PRESSED)
		{
			if (mScale > 0)
			{
				mScale -= 1.0f * Time::DeltaTime();
			}

			mCamera->SetScale(mScale);
		}
		else if (Input::GetKeyState(eKeyCode::NUM_2) == eKeyState::PRESSED)
		{
			if (mScale < 1)
			{
				mScale += 1.0f * Time::DeltaTime();
			}

			mCamera->SetScale(mScale);
		}

		mTrans->SetPosition(mPos);
	}
	
	void CameraScript::Render()
	{
	}
}