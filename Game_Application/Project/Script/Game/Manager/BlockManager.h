//==============================================================================
// File        : BlockManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"

class BlockManager : public Framework::ObjectManager {
private:
    Framework::GameObjectManager* m_GameObjectManager = nullptr;
    std::vector<Framework::GameObject*> m_Blocks;

    const int m_BlockCountX = 25;
    const int m_BlockCountZ = 25;

    float m_Timer = 0.0f;
    float m_Interval = 5.0f;  // AïbÇ≤Ç∆
    float m_BlockSpeed = 5.0f; // BÅië¨ìxÅj
    int   m_MoveCountMin = 20;
    int   m_MoveCountMax = 30;

public:
    void Create() override;
    void Update() override;

    float GetBlockHeightAt(float x, float z);
    float GetBlockHeightAt(const math::transform<math::vector3f>& transform);
};

#endif // BLOCK_MANAGER_H