#include "CrosshairScript.h"

#include "Transform.h"

#include "GameObject.h"

#include "Application.h"

#include "Input.h"

#include "Time.h"

extern arias::Application application;

namespace arias
{
	CrosshairScript::CrosshairScript() :
		Script(),
		mWinWidthCenter(0.0f),
		mWinHeightCenter(0.0f),
		mMousePos{},
		mTrans(nullptr),
		mPos{},
		mRot{}
	{
	}

	CrosshairScript::~CrosshairScript()
	{
	}

	void CrosshairScript::Initialize()
	{
		RECT winRect = {};
		GetClientRect(application.GetHwnd(), &winRect);
		mWinWidthCenter = ((float)winRect.right - (float)winRect.left) / 2.0f;
		mWinHeightCenter = ((float)winRect.bottom - (float)winRect.top) / 2.0f;

		mTrans = GetOwner()->GetComponent<Transform>();
	}

	void CrosshairScript::Update()
	{
		GetCursorPos(&mMousePos);
		ScreenToClient(application.GetHwnd(), &mMousePos);

		// Position
		mPos = mTrans->GetPosition();
		mPos.x = ((float)mMousePos.x - mWinWidthCenter) / 100.0f;
		mPos.y = -((float)mMousePos.y - mWinHeightCenter) / 100.0f;
		mTrans->SetPosition(mPos);

		// Rotation
		mRot = mTrans->GetRotation();
		mRot.z -= 3.0f * Time::DeltaTime();
		mTrans->SetRotation(mRot);
	}

	void CrosshairScript::Render()
	{
	}
}