//==============================================================================
// File        : EnemyScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef ENEMY_SCRIPT_H
#define ENEMY_SCRIPT_H

#include "GameBehaviour.h"

class EnemyScript : public Framework::GameBehaviour {
public:
    void Start() override;
    void Update() override;
};

#endif // ENEMY_SCRIPT_H