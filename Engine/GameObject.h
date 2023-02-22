#pragma once
#include "Entity.h"

#include "Component.h"

#include "Script.h"

namespace arias
{
	class GameObject : public Entity
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
		std::vector<Component*> mScripts;

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

		template <typename T>
		T* GetScript() const
		{
			T* comp;

			for (auto c : mScripts)
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
};