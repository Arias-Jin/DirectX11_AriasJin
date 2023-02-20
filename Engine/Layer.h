#pragma once
#include "Entity.h"

#include "GameObject.h"

namespace arias
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

	private:
		std::vector<GameObject*> mGameObjects;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddGameObject(GameObject* gameObject);

	public:
		const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }
	};

	typedef const std::vector<GameObject*>& GameObjects;
}