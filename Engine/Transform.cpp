#include "Transform.h"

#include "Camera.h"

#include "Renderer.h"

namespace arias
{
    Transform::Transform() :
        Component(eComponentType::Transform),
        mParent(nullptr),
        mForward(Vector3::Forward),
        mRight(Vector3::Right),
        mUp(Vector3::Up),
        mScale(Vector3::One),
        mRotation(Vector3::Zero),
        mPosition(Vector3::One)
    {
    }

    Transform::~Transform()
    {
    }

    void Transform::Initialize()
    {
    }

    void Transform::Update()
    {
        // ���� ������ ĳ���� �̵� ó��
    }

    void Transform::FixedUpdate()
    {
        // �������� ���� ��ġ������ ������Ʈ

        // ���� ��� ����

        // ũ�� ��ȯ ���
        Matrix scale = Matrix::CreateScale(mScale);

        // ȸ�� ��ȯ ���
        Matrix rotation;
        rotation = Matrix::CreateRotationX(mRotation.x);
        rotation *= Matrix::CreateRotationY(mRotation.y);
        rotation *= Matrix::CreateRotationZ(mRotation.z);

        // �̵� ��ȯ ���
        Matrix position;
        position.Translation(mPosition);

        mWorld = scale * rotation * position;

        mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
        mRight = Vector3::TransformNormal(Vector3::Right, rotation);
        mUp = Vector3::TransformNormal(Vector3::Up, rotation);

        // ī�޶� ������Ʈ���� �������ش�.
        // ����� ����
        // �������� ��� ����

        if (mParent)
        {
            mWorld *= mParent->mWorld;
        }
    }

    void Transform::Render()
    {
    }

    void Transform::SetConstantBuffer()
    {
        renderer::TransformCB trCb = {};
        trCb.world = mWorld;
        trCb.view = Camera::GetGpuViewMatrix();
        trCb.projection = Camera::GetGpuProjectionMatrix();

        ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
        cb->Bind(&trCb);

        cb->SetPipeline(eShaderStage::VS);
    }
}