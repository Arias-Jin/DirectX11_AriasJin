#pragma once

#include "Scene.h"

namespace arias
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	private:
		static Scene* mPlayScene;

	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();
	};
}