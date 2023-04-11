#pragma once
#include "ComputeShader.h"

#include "Texture.h"

namespace arias::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		~PaintShader();

	private:
		std::shared_ptr<Texture> mTarget;

	public:
		virtual void Binds() override;
		virtual void Clear() override;

	public:
		void SetTarget(std::shared_ptr<Texture> texture) { mTarget = texture; }
	};
}
