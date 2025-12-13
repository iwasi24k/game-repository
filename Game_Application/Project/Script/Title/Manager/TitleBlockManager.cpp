//==============================================================================
// File        : TitleBlockManager.cpp
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
#include "TitleBlockManager.h"
#include "Prefab/Title/TitleWhiteBlockPrefab.h"
#include "Prefab/Title/TitleBlackBlockPrefab.h"
#include "Framework/Core/Timer.h"
#include "Script/Game/BlockScript.h"

using namespace Framework;

void TitleBlockManager::Create() {
    m_GameObjectManager = GetGameObjectManager();

	TitleWhiteBlockPrefab whiteBlockPrefab;
	TitleBlackBlockPrefab blackBlockPrefab;

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

void TitleBlockManager::Update() {
	float dt = Timer::GetInstance().GetDeltaTime();
	m_Timer += dt;

	if (m_Timer < m_Interval) return;
	m_Timer = 0.0f;

	// ランダムに動かすブロック数
	int moveCount = rand_api::integer(m_MoveCountMin, m_MoveCountMax);

	// インデックスをシャッフル
	std::vector<int> indices(m_Blocks.size());
	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), rand_api::get_engine());

	constexpr float probability = 0.6f;
	constexpr float downPos = 0.0f;

	for (int i = 0; i < static_cast<int>(m_Blocks.size()); ++i) {
		auto block = m_Blocks[indices[i]];
		auto blockScript = block->GetComponent<BlockScript>();

		if (!blockScript || blockScript->IsMoving() != BlockState::Idle)
			continue;

		// 現在の高さから targetY を決定
		float upPos = block->GetTransform().scale.y;

		float targetY = rand_api::chance(probability)
			? downPos   // 下 60%
			: upPos;    // 上 40%

		// すでに targetY にいる場合はスキップ
		if (fabs(block->GetTransform().position.y - targetY) < 0.01f)
			continue;

		blockScript->StartWarning(targetY, false);

		--moveCount;
		if (moveCount <= 0) break;
	}
}