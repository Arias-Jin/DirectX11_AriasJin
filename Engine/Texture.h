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
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;

	public:
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT slot);
	};
}