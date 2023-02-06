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

	// 정점 데이터
	extern Vertex vertexes[4];

	// 메시
	extern Mesh* mesh;

	// 버퍼
	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;

	extern Shader* shader;

	void Initialize();
	void Release();
}