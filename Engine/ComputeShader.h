#pragma once
#include "Resource.h"

#include "Graphics.h"

namespace arias::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		~ComputeShader();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		bool Create(const std::wstring& file, const std::string& funcName);
		void OnExcute();

		virtual void Binds();
		virtual void Clear();
	};
}