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

#include "GameBehaviour.h"
#include "Components/RenderComponent/SpriteComponent.h"

class JumpScript : public Framework::GameBehaviour {
private:
    int m_GroundContacts = 0;
    bool m_IsGround = false;
    float m_GroundGraceTime = 0.1f;
    float m_GroundTimer = 0.0f;

    const float kCoolTime = 0.8f;
    float m_CoolTimer = kCoolTime;

public:
    void Start() override;
    void Update() override;

    void OnCollisionEnter(Framework::GameObject* other) override;
    void OnCollisionExit(Framework::GameObject* other) override;
};

#endif // JUMP_SCRIPT_H