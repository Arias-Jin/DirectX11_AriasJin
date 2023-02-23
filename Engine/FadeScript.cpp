#include "FadeScript.h"

#include "Renderer.h"

#include "Time.h"

#include "ConstantBuffer.h"

namespace arias
{
	FadeScript::FadeScript() :
		Script()
	{
	}

	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initialize()
	{
	}

	void FadeScript::Update()
	{
		// Constant Buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
		renderer::FadeCB data;
		// data.startColor = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		// data.endColor = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		data.time = Time::SecondTime();

		cb->Bind(&data);
		cb->SetPipeline(eShaderStage::VS);
		cb->SetPipeline(eShaderStage::PS);
	}

	void FadeScript::FixedUpdate()
	{
	}

	void FadeScript::Render()
	{
	}
}