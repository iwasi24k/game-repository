//==============================================================================
// File        : EnemyManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"

class EnemyManager : public Framework::ObjectManager {
private:
    Framework::GameObjectManager* m_GameObjectManager = nullptr;

    static constexpr int kEnemyMax = 5;

    float m_Timer = 0.0f;
    float m_Interval = 5.0f;  // AïbÇ≤Ç∆
    float m_BlockSpeed = 5.0f; // BÅië¨ìxÅj
    int   m_MoveCountMin = 20;
    int   m_MoveCountMax = 30;

public:
    void Create() override;
    void Update() override;
};

#endif // ENEMY_MANAGER_H