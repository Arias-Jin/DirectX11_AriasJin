#pragma once

#include "Component.h"

namespace arias
{
	class GameObject
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

	private:
		eState mState;
		std::vector<Component*> mComponents;

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddComponent(Component* comp);

	public:
		template <typename T>
		T* GetComponent() const
		{
			T* comp;

			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
				{
					return comp;
				}
			}

			return nullptr;
		}
	};
}