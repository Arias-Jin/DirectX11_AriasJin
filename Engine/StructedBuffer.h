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
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVSlot;


	public:
		bool Create(UINT size, UINT stride, eSRVType type, void* data, bool cpuAccess = false);
		void SetData(void* data, UINT bufferCount);
		void GetData(void* data, UINT size = 0);
		void BindSRV(eShaderStage stage, UINT slot);
		void BindUAV(eShaderStage stage, UINT slot);

		void Clear();

	public:
		UINT GetSize() const { return mSize; }
		UINT GetStride() const { return mStride; }

	private:
		void setDiscription();
		bool createBuffer(void* data);
		bool createView();
		bool createRWBuffer();
	};
}