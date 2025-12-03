//==============================================================================
// File        : BlockManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "BlockManager.h"
#include "Prefab/Game/WhiteBlockPrefab.h"
#include "Prefab/Game/BlackBlockPrefab.h"
#include "Framework/Core/Timer.h"
#include "Script/Game/BlockScript.h"

using namespace Framework;

void BlockManager::Create() {
    m_GameObjectManager = GetGameObjectManager();

	WhiteBlockPrefab whiteBlockPrefab;
	BlackBlockPrefab blackBlockPrefab;

	// チェス盤のようにブロックを配置
	for (int x = -m_BlockCountX / 2; x <= m_BlockCountX / 2; ++x) {
		for (int z = -m_BlockCountZ / 2; z <= m_BlockCountZ / 2; ++z) {
			Prefab& blockPrefab = ((x + z) % 2 == 0) ? static_cast<Prefab&>(whiteBlockPrefab) : static_cast<Prefab&>(blackBlockPrefab);
			auto block = blockPrefab.Create(m_GameObjectManager);
			block->GetTransform().position = math::vector3f(static_cast<float>(x * block->GetTransform().scale.x), 0.0f, static_cast<float>(z * block->GetTransform().scale.x));
			m_Blocks.push_back(block);
		}
	}
}

void BlockManager::Update() {
	float dt = Framework::Timer::GetInstance().GetDeltaTime();
	m_Timer += dt;

	if (m_Timer < m_Interval) return;
	m_Timer = 0.0f;

	// ランダムに動かすブロックを選択
	int moveCount = rand() % (m_MoveCountMax - m_MoveCountMin + 1) + m_MoveCountMin;

	std::vector<int> indices(m_Blocks.size());
	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device{}()));

	static std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	for (int i = 0; i < static_cast<int>(m_Blocks.size()); ++i) {
		auto block = m_Blocks[indices[i]];
		auto blockScript = block->GetComponent<BlockScript>();
		if (!blockScript || blockScript->IsMoving() != BlockState::Idle)
			continue;

		// 現在の高さから targetY を決定
		float targetY = 0.0f;
		float randVal = dist(mt);
		constexpr float probability = 0.6f;
		constexpr float downPos = 0.0f;
		float upPos = block->GetTransform().scale.y;

		if (randVal < probability)
			targetY = downPos; // 下 60%
		else
			targetY = upPos; // 上 40%

		// すでに targetY にいる場合はスキップ
		if (fabs(block->GetTransform().position.y - targetY) < 0.01f)
			continue;

		blockScript->StartWarning(targetY);
		--moveCount; // 選んだ分だけ減らす
		if (moveCount <= 0) break;
	}
}

float BlockManager::GetBlockHeightAt(float x, float z) {
	float maxHeight = 0.0f;

	for (auto& block : m_Blocks) {
		auto& pos = block->GetTransform().position;
		auto& scale = block->GetTransform().scale;

		// キャラクター位置がブロックのXZ範囲に入っているか
		if (x >= pos.x - scale.x / 2 && x <= pos.x + scale.x / 2 &&
			z >= pos.z - scale.z / 2 && z <= pos.z + scale.z / 2) {
			// 最大の高さを取得（複数ブロック重なっても安全）
			maxHeight = std::max(maxHeight, pos.y);
		}
	}
	return maxHeight;
}
