#include "Entity.h"

namespace arias
{
	Entity::Entity() :
		mName(L""),
		mID(reinterpret_cast<UINT64>(this))
	{
	}

	Entity::Entity(const Entity& other) :
		mName(other.mName),
		mID(reinterpret_cast<UINT64>(this))
	{
	}

	Entity::~Entity()
	{
	}
}