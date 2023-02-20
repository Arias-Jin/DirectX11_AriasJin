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
		static Scene* mActiveScene;

	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();

	public:
		static Scene* GetActiveScene() { return mActiveScene; }
	};
}