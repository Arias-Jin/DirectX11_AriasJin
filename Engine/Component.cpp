#include "Component.h"

namespace arias
{
	Component::Component(eComponentType type) :
		mType(type),
		mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}
}