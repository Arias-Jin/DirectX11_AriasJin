#include "CrosshairScript.h"

#include "Transform.h"

#include "GameObject.h"

#include "Input.h"

#include "Time.h"

namespace arias
{
	CrosshairScript::CrosshairScript() :
		Script(),
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
		mTrans = GetOwner()->GetComponent<Transform>();
	}

	void CrosshairScript::Update()
	{
#pragma region Crosshair Position
		mPos = mTrans->GetPosition();

		mPos = static_cast<Vector3>(Input::GetMouseWorldPosition());

		mTrans->SetPosition(mPos);
#pragma endregion
#pragma region Crosshair Rotation
		mRot = mTrans->GetRotation();

		mRot.z -= 3.0f * Time::DeltaTime();

		mTrans->SetRotation(mRot);
#pragma endregion
	}

	void CrosshairScript::Render()
	{
	}
}