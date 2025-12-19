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

#include "GameBehaviour.h"

class PlayerScript : public Framework::GameBehaviour {
public:
    void Start() override;
    void Update() override;
};

#endif // PLAYER_SCRIPT_H