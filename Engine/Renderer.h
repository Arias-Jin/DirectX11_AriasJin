#pragma once

#include "CommonInclude.h"
#include "Math.h"

#include "GraphicDevice_DX11.h"

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
	extern Vertex vertexes[3];

	// 버텍스 버퍼
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;

	// 버텍스 셰이더
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;

	// 픽셀 셰이더
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	// Input Layout
	extern ID3D11InputLayout* triangleLayout;

	void Initialize();
	void Release();
}