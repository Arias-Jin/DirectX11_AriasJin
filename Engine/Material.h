#pragma once
#include "Resource.h"

#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"

using namespace arias::renderer;

namespace arias::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;
		MaterialCB mCB;
		eRenderingMode mMode;

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();
		void Clear();

	public:
		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() const { return mShader; }

		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		std::shared_ptr<Texture> GetTexture() const { return mTexture; }

		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }
	};
}