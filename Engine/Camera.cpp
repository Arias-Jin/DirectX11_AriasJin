#include "Camera.h"

#include "Transform.h"

#include "GameObject.h"

#include "Application.h"

extern arias::Application application;

namespace arias
{
	Matrix Camera::mView = Matrix::Identity;
	Matrix Camera::mProjection = Matrix::Identity;

	Camera::Camera() :
		Component(eComponentType::Camera),
		mType(eProjectionType::Perspective),
		mAspectRatio(1.0f),
		mNear(1.0f),
		mFar(1000.0f),
		mScale(1.0f)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
	}

	void Camera::Render()
	{
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Create Translate View Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// 회전 정보
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 forward = tr->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = forward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = forward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = forward.z;

		mView *= viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(
				XM_2PI / 6.0f,
				mAspectRatio,
				mNear, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(
				width, height,
				mNear, mFar
			);
		}
	}
}