//==============================================================================
// File        : JumpScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef JUMP_SCRIPT_H
#define JUMP_SCRIPT_H

#include "MonoBehaviour.h"
#include "Components/RenderComponent/SpriteComponent.h"

class JumpScript : public Framework::MonoBehaviour {
private:
    int m_GroundContacts = 0;
    bool m_IsGround = false;
    float m_GroundGraceTime = 0.1f;
    float m_GroundTimer = 0.0f;

public:
    void Start() override;
    void Update() override;

    void OnTriggerEnter(Framework::GameObject* other) override;
    void OnTriggerExit(Framework::GameObject* other) override;
};

#endif // JUMP_SCRIPT_H