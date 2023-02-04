#pragma once

#include "Graphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

namespace arias::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

	private:
		// GPU °´Ã¼ »ý¼º
		ID3D11Device* mDevice;
		// GPU Read Write
		ID3D11DeviceContext* mContext;
		ID3D11Texture2D* mRenderTarget;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11Texture2D* mDepthStencilBuffer;
		ID3D11DepthStencilView* mDepthStencilView;
		IDXGISwapChain* mSwapChain;
		ID3D11SamplerState* mSampler;
	};
}