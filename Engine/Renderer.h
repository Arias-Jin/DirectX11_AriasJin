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

	// ���� ������
	extern Vertex vertexes[3];

	// ���ؽ� ����
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;

	// ���ؽ� ���̴�
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;

	// �ȼ� ���̴�
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	// Input Layout
	extern ID3D11InputLayout* triangleLayout;

	void Initialize();
	void Release();
}