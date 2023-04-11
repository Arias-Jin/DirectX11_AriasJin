#pragma once
#include "Resource.h"

#include "GraphicDevice_DX11.h"

#include "..\External\DirectXTex\Include\DirectXTex.h"

#ifdef _DEBUG
#pragma comment (lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment (lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

using namespace arias::enums;

namespace arias::graphics
{
	class Texture :public Resource
	{
	public:
		Texture();
		virtual ~Texture();

	private:
		ScratchImage mImage;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;

		D3D11_TEXTURE2D_DESC mDesc;

	public:
		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		bool Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture);
		virtual HRESULT Load(const std::wstring& name) override;
		void BindShader(eShaderStage stage, UINT slot);
		void BindUnorderedAccessView(UINT startSlot);
		void ClearUnorderedAccessView(UINT startSlot);

		void Clear();
		static void Clear(UINT startSlot);

	public:
		size_t GetWidth() const { return mImage.GetMetadata().width; }
		size_t GetHeight() const { return mImage.GetMetadata().height; }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() const { return mTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() const { return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() const { return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() const { return mUAV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() const { return mSRV; }

	};
}