//==============================================================================
// File        : PlayerHpManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef PLAYER_HP_MANAGER_H
#define PLAYER_HP_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"
#include "Global/Prefab/ScorePrefab.h"
#include "Script/Game/CombatProcessing.h"

class PlayerHpManager : public Framework::ObjectManager {
private:
    Framework::GameObject* m_Player = nullptr;
    CombatProcessing* m_CombatProcessing = nullptr;

    std::vector<Framework::GameObject*> m_HitPoints;
    int m_OldHp = -1;

public:
    void Create() override;
    void Update() override;
};

#endif // PLAYER_HP_MANAGER_H