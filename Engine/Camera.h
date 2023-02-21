#pragma once
#include "Component.h"

namespace arias
{
	using namespace math;

	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

	public:
		Camera();
		virtual ~Camera();

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;

		std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void CreateViewMatrix();
		void CreateProjectionMatrix();
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType layer, bool enable = true);

	private:
		void SortGameObjects();
		void RenderOpaque();
		void RenderCutout();
		void RenderTransparent();
		void PushGameObjectToRenderingModes(GameObject* gameObj);

	public:
		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }

		void SetProjectionType(eProjectionType type) { mType = type; }
	};
}