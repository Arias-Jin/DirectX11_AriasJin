#include "GameObject.h"

namespace arias
{
    GameObject::GameObject() :
        mState(eState::Active),
        mComponents{}
    {
        mComponents.resize((UINT)eComponentType::End);
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Initialize()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
            {
                continue;
            }

            comp->Initialize();
        }
    }

    void GameObject::Update()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
            {
                continue;
            }

            comp->Update();
        }
    }

    void GameObject::FixedUpdate()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
            {
                continue;
            }

            comp->FixedUpdate();
        }
    }

    void GameObject::Render()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
            {
                continue;
            }

            comp->Render();
        }
    }

    void GameObject::AddComponent(Component* comp)
    {
        int order = comp->GetOrder();

        mComponents[order] = comp;
        mComponents[order]->SetOwner(this);
    }
}