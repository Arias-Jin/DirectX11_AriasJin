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
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;

	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

	public:
		static void LoadScene(eSceneType type);

		static Scene* GetActiveScene() { return mActiveScene; }
	};
}