#pragma once

#include "CommonInclude.h"
#include "Math.h"

#include "GraphicDevice_DX11.h"

#include "Mesh.h"

using namespace arias::math;
using namespace arias::graphics;

namespace arias::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	// 정점 데이터
	extern Vertex vertexes[4];

	// 메시
	extern Mesh* mesh;

	// 버퍼
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;
	extern Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	// 버텍스 셰이더
	extern Microsoft::WRL::ComPtr<ID3DBlob> triangleVSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11VertexShader> triangleVS;

	// 픽셀 셰이더
	extern Microsoft::WRL::ComPtr<ID3DBlob> trianglePSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11PixelShader> trianglePS;

	// Input Layout
	extern Microsoft::WRL::ComPtr<ID3D11InputLayout> triangleLayout;

	void Initialize();
	void Release();
}