#pragma once

#include "Entity.h"

namespace arias
{
	class GameObject;

	class Component
	{
	public:
		enum class eType
		{
			None,
			Transform,
			Camera,

			// Render
			Mesh,
			SkyBox,
			Decal,

			Script,
			End,
		};

		Component();
		virtual ~Component();

	private:
		const eType mType;
		GameObject* mOwner;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	};
}