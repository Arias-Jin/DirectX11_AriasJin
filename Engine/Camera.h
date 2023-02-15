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

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();

	public:
		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }
	};
}