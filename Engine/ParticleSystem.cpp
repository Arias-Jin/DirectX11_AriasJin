#include "ParticleSystem.h"

#include "Transform.h"

#include "GameObject.h"

#include "StructedBuffer.h"

#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"

#include "Time.h"

namespace arias
{
	ParticleSystem::ParticleSystem() :
		BaseRenderer(eComponentType::ParticleSystem),
		mBuffer(nullptr),
		mSharedBuffer(nullptr),
		mCount(100),
		mStartSize(Vector4::Zero),
		mEndSize(Vector4::Zero),
		mStartColor(Vector4::Zero),
		mEndColor(Vector4::Zero),
		mStartLifeTime(0.0f), 
		mFrequency(1.0f),
		mTime(0.0f),
		mCBData{}
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;

		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
		mCS = ResourceManager::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = ResourceManager::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material 세팅
		std::shared_ptr<Material> material = ResourceManager::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = ResourceManager::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[i].active = 0;
			particles[i].direction = Vector4(cosf((float)i * (XM_2PI / (float)mCount)), sin((float)i * (XM_2PI / (float)mCount)), 0.0f, 1.0f);
			particles[i].speed = 100.0f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);

		mSharedBuffer = new StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
		//파티클 생성 시간
		float aliveTime = 1.0f / mFrequency;
		//누적시간
		mTime += Time::DeltaTime();

		if (aliveTime < mTime)
		{
			float f = (mTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5, };
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  };
			mSharedBuffer->SetData(&shared, 1);
		}

		mCBData.elementCount = mBuffer->GetStride();
		mCBData.deltaTime = Time::DeltaTime();
		mCBData.elapsedTime += Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::CS);

		mCS->SetSharedStrutedBuffer(mSharedBuffer);
		mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}
}