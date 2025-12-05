//==============================================================================
// File        : GameBehaviour.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef MONO_BEHAVIOUR_H
#define MONO_BEHAVIOUR_H

#include "Behaviour.h"

namespace Framework {

    class Scene;
    class ManagerHub;

    class GameBehaviour : public Behaviour {
    public:
        // --- user API ---
        Scene* GetScene();
        ManagerHub* GetManagerHub();
    };
}

#endif // MONO_BEHAVIOUR_H