#pragma once
#include "ComputeShader.h"

#include "StructedBuffer.h"

namespace arias::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

	private:
		StructedBuffer* mBuffer;

	public:
		virtual void Binds() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(StructedBuffer* buffer);
	};
}
