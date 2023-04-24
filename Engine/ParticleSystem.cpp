#include "ParticleSystem.h"

#include "Transform.h"

#include "GameObject.h"

#include "StructedBuffer.h"

#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"

namespace arias
{
	ParticleSystem::ParticleSystem() :
		BaseRenderer(eComponentType::ParticleSystem),
		mBuffer(nullptr),
		mCount(100),
		mStartSize(Vector4::Zero),
		mEndSize(Vector4::Zero),
		mStartColor(Vector4::Zero),
		mEndColor(Vector4::Zero),
		mStartLifeTime(0.0f)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}

	void ParticleSystem::Initialize()
	{
		mCS = ResourceManager::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = ResourceManager::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material ¼¼ÆÃ
		std::shared_ptr<Material> material = ResourceManager::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = ResourceManager::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);

		for (size_t i = 0; i < mCount; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[i].active = 1;
			particles[i].direction = Vector4(cosf((float)i * (XM_2PI / (float)mCount)), sin((float)i * (XM_2PI / (float)mCount)), 0.0f, 1.0f);
			particles[i].speed = 100.0f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eSRVType::UAV, particles);
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::FixedUpdate()
	{
		mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 15);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}
}
