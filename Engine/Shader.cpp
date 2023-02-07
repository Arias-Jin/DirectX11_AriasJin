#include "Shader.h"

#include "GraphicDevice_DX11.h"

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

	void Shader::Create(graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		mErrorBlob = nullptr;

		// Vertex Shader
		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\SHADER_SOURCE\\";

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
	}
}