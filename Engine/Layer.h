#pragma once
#include "Entity.h"

namespace arias
{
	class GameObject;

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
		virtual void Destroy();

	public:
		void AddGameObject(GameObject* gameObject);

	public:
		const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }

		std::vector<GameObject*> GetDontDestroyGameObjects();
	};

	typedef const std::vector<GameObject*>& GameObjects;
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}