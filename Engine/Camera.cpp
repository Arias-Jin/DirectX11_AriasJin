#include "Camera.h"

#include "BaseRenderer.h"
#include "Transform.h"

#include "GameObject.h"

#include "Application.h"

#include "Renderer.h"

#include "Material.h"

#include "Scene.h"
#include "SceneManager.h"

extern arias::Application application;

namespace arias
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera() :
		Component(eComponentType::Camera),
		mView{},
		mProjection{},
		mType(eProjectionType::Orthographic),
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
		EnableLayerMasks();
		RegisterCameraInRenderer();
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		SortGameObjects();

		RenderOpaque();
		RenderCutout();
		RenderTransparent();
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

		float width = ((float)winRect.right - (float)winRect.left) * mScale;
		float height = ((float)winRect.bottom - (float)winRect.top) * mScale;
		
		if (width <= 0.0f || height <= 0.0f)
		{
			width = 0.1f;
			height = 0.1f;
		}

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
	
	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	void Camera::SortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();

		for (size_t i = 0; i < (UINT)eLayerType::End; ++i)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();

				if (gameObjects.size() == 0)
				{
					continue;
				}

				for (GameObject* obj : gameObjects)
				{
					PushGameObjectToRenderingModes(obj);
				}
			}
		}
	}

	void Camera::RenderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}

			obj->Render();
		}
	}
	
	void Camera::RenderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}

			obj->Render();
		}
	}
	
	void Camera::RenderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}

			obj->Render();
		}
	}
	
	void Camera::PushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer = gameObj->GetComponent<BaseRenderer>();

		if (renderer == nullptr)
		{
			return;
		}

		std::shared_ptr<Material> material = renderer->GetMaterial();
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case arias::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case arias::graphics::eRenderingMode::Cutout:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case arias::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}