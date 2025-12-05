//==============================================================================
// File        : BgBlockManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "BgBlockManager.h"
#include "Prefab/Title/BlockPrefab.h"
#include "Framework/Core/Timer.h"
#include "Script/Game/BlockScript.h"
#include <Script/Title/BgBlockScript.h>

using namespace Framework;

void BgBlockManager::Create() {
    BlockPrefab blockPrefab;

    for (int i = 0; i < kMaxBlock; ++i) {
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_real_distribution<float> dist(0.0f, 20.0f);

        auto obj = BlockPrefab().Create(GetGameObjectManager());
        auto bgBlock = obj->GetComponent<BgBlockScript>();
        bgBlock->FallStartTime(dist(mt));
        m_Blocks.push_back(obj);
    }
}

void BgBlockManager::Update() {

}