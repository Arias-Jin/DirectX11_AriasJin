#include "GameObject.h"

#include "Transform.h"

namespace arias
{
    GameObject::GameObject() :
        mState(eState::Active),
        mType(eLayerType::None),
        mComponents{},
        mScripts{},
        mbDontDestroy(false)
    {
        mComponents.resize((UINT)eComponentType::End);
    }

    GameObject::~GameObject()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
            {
                continue;
            }

            delete comp;
            comp = nullptr;
        }

        for (Component* script : mScripts)
        {
            if (script == nullptr)
            {
                continue;
            }

            delete script;
            script = nullptr;
        }
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

        for (Component* script : mScripts)
        {
            if (script == nullptr)
            {
                continue;
            }

            script->Initialize();
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

        for (Component* script : mScripts)
        {
            if (script == nullptr)
            {
                continue;
            }

            script->Update();
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

        for (Component* script : mScripts)
        {
            if (script == nullptr)
            {
                continue;
            }

            script->FixedUpdate();
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

        for (Component* script : mScripts)
        {
            if (script == nullptr)
            {
                continue;
            }

            script->Render();
        }
    }

    void GameObject::AddComponent(Component* comp)
    {
        eComponentType order = comp->GetOrder();

        if (order != eComponentType::Script)
        {
            mComponents[(UINT)order] = comp;
            mComponents[(UINT)order]->SetOwner(this);
        }
        else
        {
            mScripts.push_back(comp);
            comp->SetOwner(this);
        }
    }
}