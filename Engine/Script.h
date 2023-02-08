#pragma once
#include "Component.h"

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
    };
}

