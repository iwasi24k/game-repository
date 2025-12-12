//==============================================================================
// File        : ShadowScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef SHADOW_SCRIPT_H
#define SHADOW_SCRIPT_H

#include "GameBehaviour.h"

class ShadowScript : public Framework::GameBehaviour {
public:
    void Start() override;
    void Update() override;
};

#endif // SHADOW_SCRIPT_H