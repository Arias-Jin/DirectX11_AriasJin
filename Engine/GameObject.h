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
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mbDontDestroy;

	protected:
		std::vector<Component*> mComponents;

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

		void SetDontDestroy(bool enable) { mbDontDestroy = enable; }
		bool GetDontDestroy() const { return mbDontDestroy; }

		void SetLayerType(eLayerType type) { mType = type; }
		eLayerType GetLayerType() const { return mType; }

		const std::vector<Script*>& GetScripts() { return mScripts; }

	public:
		Transform* GetTransform()
		{
			if (mComponents[(UINT)eComponentType::Transform])
			{
				return static_cast<Transform*>(mComponents[(UINT)eComponentType::Transform]);
			}

			return nullptr;
		}

		Vector3 GetPosition() { return GetTransform()->GetPosition(); }
		float GetPositionX() { return GetTransform()->GetPositionX(); }
		float GetPositionY() { return GetTransform()->GetPositionY(); }
		float GetPositionZ() { return GetTransform()->GetPositionZ(); }
		Vector2 GetPositionXY() { return GetTransform()->GetPositionXY(); }

		Vector3 GetRotation() { return GetTransform()->GetRotation(); }
		float GetRotationX() { return GetTransform()->GetRotationX(); }
		float GetRotationY() { return GetTransform()->GetRotationY(); }
		float GetRotationZ() { return GetTransform()->GetRotationZ(); }
		Vector2 GetRotationXY() { return GetTransform()->GetRotationXY(); }

		Vector3 GetScale() { return GetTransform()->GetScale(); }
		float GetScaleX() { return GetTransform()->GetScaleX(); }
		float GetScaleY() { return GetTransform()->GetScaleY(); }
		float GetScaleZ() { return GetTransform()->GetScaleZ(); }
		Vector2 GetScaleXY() { return GetTransform()->GetScaleXY(); }

		void SetPosition(const Vector3& position) { GetTransform()->SetPosition(position); }
		void SetPositionX(const float positionX) { GetTransform()->SetPositionX(positionX); }
		void SetPositionY(const float positionY) { GetTransform()->SetPositionY(positionY); }
		void SetPositionZ(const float positionZ) { GetTransform()->SetPositionZ(positionZ); }
		void SetPositionXY(const Vector2& position) { GetTransform()->SetPositionXY(position); }

		void SetRotation(const Vector3& rotation) { GetTransform()->SetRotation(rotation); }
		void SetRotationX(const float rotationX) { GetTransform()->SetRotationX(rotationX); }
		void SetRotationY(const float rotationY) { GetTransform()->SetRotationY(rotationY); }
		void SetRotationZ(const float rotationZ) { GetTransform()->SetRotationZ(rotationZ); }
		void SetRotationXY(const Vector2& rotation) { GetTransform()->SetRotationXY(rotation); }

		void SetScale(const Vector3& scale) { GetTransform()->SetScale(scale); }
		void SetScaleX(const float scaleX) { GetTransform()->SetScaleX(scaleX); }
		void SetScaleY(const float scaleY) { GetTransform()->SetScaleY(scaleY); }
		void SetScaleZ(const float scaleZ) { GetTransform()->SetScaleZ(scaleZ); }
		void SetScaleXY(const Vector2& scale) { GetTransform()->SetScaleXY(scale); }

	public:
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
				mScripts.push_back(dynamic_cast<Script*>(comp));
				comp->SetOwner(this);
			}

			// comp->Initialize();

			return comp;
		}

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
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};

			T* comp;

			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
				{
					components.push_back(comp);
				}
			}

			return components;
		}
	};
};