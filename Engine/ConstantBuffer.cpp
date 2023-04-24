#include "ConstantBuffer.h"

#include "GraphicDevice_DX11.h"

namespace arias::graphics
{
    ConstantBuffer::ConstantBuffer(eCBType type) :
        mType(type)
    {
    }

    ConstantBuffer::~ConstantBuffer()
    {
    }

    bool ConstantBuffer::Create(size_t size)
    {
        // 상수버퍼
        desc.ByteWidth = (UINT)size;
        desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
        desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        if (!GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()))
        {
            return false;
        }

        return true;
    }

    void ConstantBuffer::SetData(void* data)
    {
        GetDevice()->SetData(buffer.Get(), data, desc.ByteWidth);
    }

    void ConstantBuffer::Bind(eShaderStage stage)
    {
        GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
    }
}