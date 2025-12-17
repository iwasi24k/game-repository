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
private:
    float m_StopRadius = 5.0f;
    float m_SlowRadius = 10.0f;
    float m_MaxSpeed = 3.0f;

    float m_EnemyAvoidRadius = 4.5f;
    float m_EnemyAvoidPower = 3.0f;

    float m_SideMoveTimer = 0.0f;
    float m_SideMoveInterval = 2.5f;   // âΩïbÇ≤Ç∆Ç…êÿÇËë÷Ç¶ÇÈÇ©
    int   m_SideDir = 1;               // +1 or -1
    float m_SideWeight = 0.6f;   // â°à⁄ìÆÇÃã≠Ç≥

    bool  m_IsSideMove = false;
    float m_SideMoveDuration = 1.2f;   // â°à⁄ìÆÇµÇƒÇ¢ÇÈéûä‘

    float m_CurrentSideWeight = 0.0f;

public:
    void Start() override;
    void Update() override;

private:
    void UpdatePositionY(Framework::GameObject* player, float dt);

    math::vector3f ComputeForwardMovement(const math::vector3f& toPlayer, float distance);
    math::vector3f ComputeSideMovement(const math::vector3f& toPlayer, float distance);
    math::vector3f ComputeSeparation(const math::vector3f& pos);
};

#endif // ENEMY_SCRIPT_H