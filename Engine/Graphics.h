#pragma once

#include "Math.h"

namespace arias::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		PS,
		Count,
	};
}