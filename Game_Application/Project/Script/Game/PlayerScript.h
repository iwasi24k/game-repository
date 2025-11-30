//==============================================================================
// File        : PlayerScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef PLAYER_SCRIPT_H
#define PLAYER_SCRIPT_H

#include "MonoBehaviour.h"

class PlayerScript : public Framework::MonoBehaviour {
public:
    void Start() override;
    void Update() override;

    //void OnTriggerEnter(Framework::GameObject* other) override;
    //void OnTriggerExit(Framework::GameObject* other) override;
};

#endif // PLAYER_SCRIPT_H