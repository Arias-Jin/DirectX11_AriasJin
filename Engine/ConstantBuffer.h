#pragma once
#include "Graphics.h"

using namespace arias::enums;

namespace arias::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer();
		virtual ~ConstantBuffer();

	private:
		const eCBType mType;

	public:
		bool Create(size_t size);
		void Bind(void* data);
		void SetPipeline(eShaderStage stage);
	};
}