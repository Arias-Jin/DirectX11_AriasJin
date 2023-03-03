#pragma once
#include "Scene.h"

namespace arias
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

	private:

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}