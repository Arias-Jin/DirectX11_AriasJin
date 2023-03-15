#include "Shader.h"

#include "GraphicDevice_DX11.h"

#include "Renderer.h"

using namespace arias::graphics;

namespace arias
{
	Shader::Shader() :
		Resource(eResourceType::GraphicShader),
		mInputLayout(nullptr),
		mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
		mStage{},
		mVSBlob(nullptr),
		mHSBlob(nullptr),
		mDSBlob(nullptr),
		mGSBlob(nullptr),
		mPSBlob(nullptr),
		mVS(nullptr),
		mHS(nullptr),
		mDS(nullptr),
		mGS(nullptr),
		mPS(nullptr),
		mRSType(eRSType::SolidBack),
		mDSType(eDSType::Less),
		mBSType(eBSType::AlphaBlend),
		mErrorBlob(nullptr)
	{
	}

	Shader::~Shader()
	{
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Shader::Create(eShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		mErrorBlob = nullptr;

		// Vertex Shader
		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\..\\SHADER_SOURCE\\";

		std::wstring shaderPath(path.c_str());
		shaderPath += file;

		if (stage == graphics::eShaderStage::VS)
		{
			D3DCompileFromFile(
				shaderPath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				funcName.c_str(),
				"vs_5_0",
				0, 0,
				mVSBlob.GetAddressOf(),
				mErrorBlob.GetAddressOf()
			);

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				// mErrorBlob->Release();
			}

			GetDevice()->CreateVertexShader(
				mVSBlob->GetBufferPointer(),
				mVSBlob->GetBufferSize(),
				nullptr,
				mVS.GetAddressOf()
			);
		}
		else if (stage == graphics::eShaderStage::PS)
		{
			D3DCompileFromFile(
				shaderPath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				funcName.c_str(),
				"ps_5_0",
				0, 0,
				mPSBlob.GetAddressOf(),
				mErrorBlob.GetAddressOf()
			);

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				// mErrorBlob->Release();
			}

			GetDevice()->CreatePixelShader(
				mPSBlob->GetBufferPointer(),
				mPSBlob->GetBufferSize(),
				nullptr,
				mPS.GetAddressOf()
			);
		}
	}

	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout.Get());

		GetDevice()->BindVertexShader(mVS.Get(), nullptr, 0);
		GetDevice()->BindPixelShader(mPS.Get(), nullptr, 0);

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rs = renderer::rasterizerStates[(UINT)mRSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds = renderer::depthstencilStates[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bs = renderer::blendStates[(UINT)mBSType];

		GetDevice()->BindRasterizerState(rs.Get());
		GetDevice()->BindDepthStencilState(ds.Get());
		GetDevice()->BindBlendState(bs.Get());
	}
}