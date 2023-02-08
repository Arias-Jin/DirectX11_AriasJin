#pragma once
#include "Resource.h"

#include "Renderer.h"

#include "Shader.h"

using namespace arias::renderer;

namespace arias::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

	private:
		Shader* mShader;
		MaterialCB mCB;

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();

	public:
		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() const { return mShader; }
	};
}