//==============================================================================
// File        : Collider.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
// Overview :
// Framework/Scene/Components/PhysicsComponent/.h
//==============================================================================
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Behaviour.h"
#include "MathTransform.h"

namespace Framework {

    class ColliderComponent : public Behaviour {
    private:
        bool m_IsTrigger = false;

    public:
        virtual void Update() override = 0;

        bool IsTrigger() const { return m_IsTrigger; }
    };
}

#endif // COLLIDER_H