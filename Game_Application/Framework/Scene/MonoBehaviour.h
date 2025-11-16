//==============================================================================
// File        : MonoBehaviour.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef MONO_BEHAVIOUR_H
#define MONO_BEHAVIOUR_H

#include "Behaviour.h"

namespace Framework {

    class MonoBehaviour : public Behaviour {
    public:
        // --- user API ---


        // -----------------------------------------------
        // --- Example MonoBehaviour ---
        // class PlayerScript : public MonoBehaviour {
        // public:
        //     void Start() override {
        //         // Initialization code here
        //     }
        //   
        //     void Update() override {
        //         // Update code here
        //     }
        // };
        // -----------------------------------------------
    };
}

#endif // MONO_BEHAVIOUR_H