#pragma once

namespace arias::enums
{
	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		MousePointer,
		Player,
		Enemy,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		// Collider2,
		MeshRenderer,
		SpriteRenderer,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		// Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};
}