#include "Material.h"

namespace arias::graphics
{
    Material::Material() :
        Resource(eResourceType::Material),
        mShader(nullptr),
        mCB{},
        mMode(eRenderingMode::Opaque)
    {
    }

    Material::~Material()
    {
    }

    HRESULT Material::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    void Material::SetData(eGPUParam param, void* data)
    {
        switch (param)
        {
        case arias::graphics::eGPUParam::Int:
            mCB.iData = *static_cast<int*>(data);
            break;
        case arias::graphics::eGPUParam::Float:
            mCB.fData = *static_cast<float*>(data);
            break;
        case arias::graphics::eGPUParam::Vector2:
            mCB.xy = *static_cast<Vector2*>(data);
            break;
        case arias::graphics::eGPUParam::Vector3:
            mCB.xyz = *static_cast<Vector3*>(data);
            break;
        case arias::graphics::eGPUParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case arias::graphics::eGPUParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
        default:
            break;
        }
    }

    void Material::Bind()
    {
        for (size_t i = 0; i < (UINT)eTextureSlot::End; i++)
        {
            if (mTexture[i] == nullptr)
            {
                continue;
            }

            mTexture[i]->BindShaderResource(eShaderStage::VS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::HS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::DS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::GS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::PS, (UINT)i);
            mTexture[i]->BindShaderResource(eShaderStage::CS, (UINT)i);
        }

        ConstantBuffer* pCB = renderer::constantBuffers[(UINT)eCBType::Material];
        pCB->SetData(&mCB);
        pCB->Bind(eShaderStage::VS);
        pCB->Bind(eShaderStage::GS);
        pCB->Bind(eShaderStage::PS);

        mShader->Binds();
    }

    void Material::Clear()
    {
        for (size_t i = 0; i < (UINT)eTextureSlot::End; i++)
        {
            if (mTexture[i] == nullptr)
            {
                continue;
            }

            mTexture[i]->Clear();
        }
    }
}
