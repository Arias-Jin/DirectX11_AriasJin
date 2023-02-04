#include "GraphicDevice_DX11.h"

namespace arias::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11() :
		mDevice(nullptr),
		mContext(nullptr),
		mRenderTarget(nullptr),
		mRenderTargetView(nullptr),
		mDepthStencilBuffer(nullptr),
		mDepthStencilView(nullptr),
		mSwapChain(nullptr),
		mSampler(nullptr)
	{
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
	}
}