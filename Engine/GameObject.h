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
		bool IsDead()
		{
			if (mState == eState::Dead)
			{
				return true;
			}

			return false;
		}

		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }

		eState GetState() const { return mState; }

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

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			eComponentType order = comp->GetOrder();

			if (order != eComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(comp);
				comp->SetOwner(this);
			}

			return comp;
		}
	};
};