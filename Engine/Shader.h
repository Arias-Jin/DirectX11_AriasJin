#pragma once
#include "Resource.h"

#include "Graphics.h"

namespace arias
{
	class Shader : public Resource
	{
	public:
		Shader();
		~Shader();

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		graphics::eShaderStage mStage;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		void Create(graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName);
		void Binds();

	public:
		ID3D11InputLayout* GetInputLayout() const { return mInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return mInputLayout.GetAddressOf(); }

		void* GetVSBlobBufferPointer() const { return mVSBlob->GetBufferPointer(); }
		SIZE_T GetVSBlobBufferSize() const { return mVSBlob->GetBufferSize(); }
	};
}