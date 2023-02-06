#pragma once

#include "CommonInclude.h"
#include "Math.h"

#include "GraphicDevice_DX11.h"

#include "Mesh.h"
#include "Shader.h"

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
	extern Vertex vertexes[4];

	// �޽�
	extern Mesh* mesh;

	// ����
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;

	extern Shader* shader;

	void Initialize();
	void Release();
}