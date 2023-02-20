#include "CrosshairScript.h"

#include "Transform.h"

#include "GameObject.h"

#include "Application.h"

#include "Input.h"

extern arias::Application application;

namespace arias
{
	CrosshairScript::CrosshairScript() :
		Script(),
		mWinWidthCenter(0.0f),
		mWinHeightCenter(0.0f)
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
	}

	void CrosshairScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);

		pos.x = ((float)mousePos.x - mWinWidthCenter) / 100.0f;
		pos.y = -((float)mousePos.y - mWinHeightCenter) / 100.0f;

		tr->SetPosition(pos);
	}

	void CrosshairScript::Render()
	{
	}
}