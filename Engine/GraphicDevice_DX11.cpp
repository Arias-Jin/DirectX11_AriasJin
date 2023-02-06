#include "GraphicDevice_DX11.h"

#include "Application.h"

#include "Renderer.h"

extern arias::Application application;

namespace arias::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11(ValidationMode validationMode) :
		mDevice(nullptr),
		mContext(nullptr),
		mRenderTarget(nullptr),
		mRenderTargetView(nullptr),
		mDepthStencilBuffer(nullptr),
		mDepthStencilView(nullptr),
		mSwapChain(nullptr),
		mViewPort{}
	{
		HWND hwnd = application.GetHwnd();

		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		// Device
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			DeviceFlag,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			mDevice.GetAddressOf(),
			&FeatureLevel,
			mContext.GetAddressOf()
		);

		// SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
		{
			return;
		}

		// Get RenderTarget for SwapChain
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		// Create RenderTarget View
		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthBuffer = {};

		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;
		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Width = application.GetWidth();
		depthBuffer.Height = application.GetHeight();
		depthBuffer.ArraySize = 1;
		depthBuffer.SampleDesc.Count = 1;
		depthBuffer.SampleDesc.Quality = 0;
		depthBuffer.MipLevels = 0;
		depthBuffer.MiscFlags = 0;

		// Depth Stencil Buffer
		if (!CreateTexture(&depthBuffer, mDepthStencilBuffer.GetAddressOf()))
		{
			return;
		}

		// Depth Stencil Buffer View
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
		{
			return;
		}

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f, 1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		renderer::Release();
	}

	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
		{
			return false;
		}

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
		{
			return false;
		}

		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
		{
			return false;
		}

		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(desc, NumElements, byteCode, bytecodeLength, ppInputLayout)))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer)
	{
		// System -> GPU
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
		{
			return false;
		}

		return true;
	}

	bool GraphicDevice_DX11::CreateShader()
	{
		ID3DBlob* errorBlob = nullptr;

		// Vertex Shader
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += "\\SHADER_SOURCE\\";

		std::wstring vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";
		D3DCompileFromFile(
			vsPath.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"VS_Test",
			"vs_5_0",
			0,
			0,
			&renderer::triangleVSBlob,
			&errorBlob
		);

		mDevice->CreateVertexShader(
			renderer::triangleVSBlob->GetBufferPointer(),
			renderer::triangleVSBlob->GetBufferSize(),
			nullptr,
			&renderer::triangleVS
		);

		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}

		std::wstring psPath(shaderPath.c_str());
		psPath += L"TrianglePS.hlsl";
		D3DCompileFromFile(
			psPath.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"PS_Test",
			"ps_5_0",
			0,
			0,
			&renderer::trianglePSBlob,
			&errorBlob
		);

		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			errorBlob = nullptr;
		}

		mDevice->CreatePixelShader(
			renderer::trianglePSBlob->GetBufferPointer(),
			renderer::trianglePSBlob->GetBufferSize(),
			nullptr,
			&renderer::trianglePS
		);

		return true;
	}

	void GraphicDevice_DX11::BindViewports(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void GraphicDevice_DX11::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void GraphicDevice_DX11::SetConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case arias::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case arias::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case arias::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case arias::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case arias::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case arias::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::Draw()
	{
		// 리소스 바인딩
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(renderer::triangleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, renderer::vertexes, sizeof(renderer::Vertex) * 4);
		mContext->Unmap(renderer::triangleBuffer, 0);

		// Clear RenderTarget
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		// 상수 버퍼를 셰이더에 세팅
		SetConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer);

		// Input Assembler 단계에 버텍스 버퍼 정보 지정
		UINT vertexSize = sizeof(renderer::Vertex);
		UINT offset = 0;

		mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexSize, &offset);
		mContext->IASetIndexBuffer(renderer::triangleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		mContext->IASetInputLayout(renderer::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 생성된 셰이더 세팅
		mContext->VSSetShader(renderer::triangleVS, 0, 0);
		mContext->PSSetShader(renderer::trianglePS, 0, 0);
		
		mContext->DrawIndexed(6, 0, 0);

		// 백버퍼에 그리기
		mSwapChain->Present(0, 0);
	}
}