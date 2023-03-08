#include "DebugObject.h"

namespace arias
{
	DebugObject::DebugObject()
	{
	}

	DebugObject::~DebugObject()
	{
	}

	void DebugObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->FixedUpdate();
		}
	}
}