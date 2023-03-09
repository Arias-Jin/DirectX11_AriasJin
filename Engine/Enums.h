#pragma once

namespace arias::enums
{
	enum class eSceneType
	{
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Player,
		Enemy,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
		Collider,
		// Collider2,
		MeshRenderer,
		SpriteRenderer,
		Animator,
		UI,
		Fade,
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

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};
}