#pragma once
#include "Graphics.h"

#include "Entity.h"

namespace arias::graphics
{
	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;

	public:
		bool Create(UINT size, UINT stride, eSRVType type, void* data);
		void Bind(void* data, UINT bufferCount);
		void SetPipeline(eShaderStage stage, UINT slot);

	public:
		UINT GetSize() const { return mSize; }
		UINT GetStride() const { return mStride; }
	};
}