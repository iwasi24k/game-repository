//==============================================================================
// File        : TitleBlockManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef TITLE_BLOCK_MANAGER_H
#define TITLE_BLOCK_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"

class TitleBlockManager : public Framework::ObjectManager {
private:
    Framework::GameObjectManager* m_GameObjectManager = nullptr;
    std::vector<Framework::GameObject*> m_Blocks;

    const int m_BlockCountX = 23;
    const int m_BlockCountZ = 23;

    float m_Timer = 0.0f;
    float m_Interval = 5.0f;  // AïbÇ≤Ç∆
    float m_BlockSpeed = 5.0f; // BÅië¨ìxÅj
    int   m_MoveCountMin = 20;
    int   m_MoveCountMax = 30;

public:
    void Create() override;
    void Update() override;
};

#endif // TITLE_BLOCK_MANAGER_H