#pragma once
#include "BaseRenderer.h"

#include "ParticleShader.h"

namespace arias
{
	enum class eSimulationSpace
	{
		Local,
		World,
	};

	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<graphics::ParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		Vector4 mStartSize;
		Vector4 mStartColor;

		eSimulationSpace mSimulationSpace;
		UINT mMaxParticles;

		float mStartLifeTime;
		float mFrequency;
		float mRadius;
		float mStartSpeed;
		float mTime;
		float mElapsedTime; //누적시간

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}