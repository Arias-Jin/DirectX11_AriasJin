#pragma once

#include "Graphics.h"

namespace arias::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11(ValidationMode validationMode = ValidationMode::Disabled);
		~GraphicDevice_DX11();

	private:
		// GPU ��ü ����(�׷���ī��� ����Ǵ� �⺻���� ��ü)
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		// GPU Read Write(����̽��� ���� �������� �ʰ� �� ��ü�� ���ؼ� GPU�� ����� ����)
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// ���������� �׷����� ��ȭ��
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// �����(FrameBuffer)�� �����ϰ�, ������ ȭ�鿡 �������ϴ� ������ ���
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		// �ؽ�ó�� �ε��� �� ���
		// Microsoft::WRL::ComPtr<ID3D11SamplerState> mSampler;

		D3D11_VIEWPORT mViewPort;

	public:
		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc);
		bool CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D);

		bool CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer);
		bool CreateShader();
		void BindViewports(D3D11_VIEWPORT* viewPort);

		void Draw();
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;

		return device;
	}
}