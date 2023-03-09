#pragma once
#include "Component.h"

#include "Collider2D.h"

namespace arias
{
    class Script : public Component
    {
    public:
        Script();
        virtual ~Script();

    private:

    public:
        virtual void Initialize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();

    public:
        virtual void OnCollisionEnter(Collider2D* collider) {};
        virtual void OnCollisionStay(Collider2D* collider) {};
        virtual void OnCollisionExit(Collider2D* collider) {};

        virtual void OnTriggerEnter(Collider2D* collider) {};
        virtual void OnTriggerStay(Collider2D* collider) {};
        virtual void OnTriggerExit(Collider2D* collider) {};
    };
}

