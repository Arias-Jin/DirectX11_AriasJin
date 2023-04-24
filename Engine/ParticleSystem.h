#pragma once
#include "BaseRenderer.h"

#include "ParticleShader.h"

namespace arias
{
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

	private:
		class StructedBuffer* mBuffer;
		std::shared_ptr<graphics::ParticleShader> mCS;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}