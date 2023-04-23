#pragma once
#include "Graphics.h"

using namespace arias::enums;

namespace arias::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

	private:
		const eCBType mType;

	public:
		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);
	};
}