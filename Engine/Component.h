#pragma once
#include "Entity.h"

#include "Math.h"

using namespace arias::enums;

namespace arias
{
	class GameObject;

	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

	private:
		const eComponentType mType;
		GameObject* mOwner;

	public:
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

	public:
		eComponentType GetOrder() const { return mType; }

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() const { return mOwner; }
	};
}