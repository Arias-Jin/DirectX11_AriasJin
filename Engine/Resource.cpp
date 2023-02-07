#include "Resource.h"

namespace arias
{
	Resource::Resource(eResourceType type) :
		mKey{},
		mPath{},
		mType(type)
	{
	}

	Resource::~Resource()
	{
		int a = 0;
	}
}