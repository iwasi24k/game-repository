//==============================================================================
// File        : BgBlockManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef BG_BLOCK_MANAGER_H
#define BG_BLOCK_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"

class BgBlockManager : public Framework::ObjectManager {
private:
    std::vector<Framework::GameObject*> m_Blocks;

    static constexpr int kMaxBlock = 50;
    float m_SpawnInterval = 0.2f; // 秒単位
    float m_SpawnTimer = 0.0f;  // 経過タイマー

public:
    void Create() override;
    void Update() override;
};

#endif // BG_BLOCK_MANAGER_H