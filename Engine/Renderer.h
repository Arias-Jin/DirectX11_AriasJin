#pragma once

#include "CommonInclude.h"
#include "Math.h"

#include "GraphicDevice_DX11.h"

#include "Mesh.h"
#include "Shader.h"

#include "ConstantBuffer.h"

using namespace arias::math;
using namespace arias::graphics;

namespace arias::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	// ���� ������
	extern Vertex vertexes[4];

	// ��� ����
	extern ConstantBuffer* constantBuffers[];

	void Initialize();
	void Release();
}