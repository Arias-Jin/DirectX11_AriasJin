#include "GridScript.h"

#include "Transform.h"
#include "Camera.h"

#include "GameObject.h"

#include "Application.h"

#include "Renderer.h"

#include "SceneManager.h"

#include "ConstantBuffer.h"

extern arias::Application application;

namespace arias
{
	GridScript::GridScript() :
		Script(),
		mObject(nullptr),
		mTrans(nullptr),
		mCamera(nullptr),
		mWinResolution{},
		mCameraPos{},
		mPos{},
		mScale(0.0f)
	{
	}

	GridScript::~GridScript()
	{
	}

	void GridScript::Initialize()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		mCamera = renderer::cameras[(UINT)type][0];

		RECT winRect;;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = (float)winRect.right - (float)winRect.left;
		float height = (float)winRect.bottom - (float)winRect.top;

		mWinResolution.x = width;
		mWinResolution.y = height;

		mObject = mCamera->GetOwner();
		mTrans = mObject->GetComponent<Transform>();
	}	 
		 
	void GridScript::Update()
	{
		if (mCamera == nullptr)
		{
			return;
		}

		mCameraPos = mTrans->GetPosition();
		mPos = Vector4(mCameraPos.x, mCameraPos.y, mCameraPos.z, 1.0f);
		mScale = mCamera->GetScale();

		// Constant Buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = mPos;
		data.cameraScale = Vector2(mScale, mScale);
		data.resolution = mWinResolution;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}	 
		 
	void GridScript::FixedUpdate()
	{	 
	}	 
		 
	void GridScript::Render()
	{
	}
}