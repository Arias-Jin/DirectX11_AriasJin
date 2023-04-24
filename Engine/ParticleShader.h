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
		StructedBuffer* mSharedBuffer;

	public:
		virtual void Binds() override;
		virtual void Clear() override;

	public:
		void SetStrcutedBuffer(StructedBuffer* buffer) { mBuffer = buffer; }
		void SetSharedStrutedBuffer(StructedBuffer* buffer) { mSharedBuffer = buffer; }
	};
}
