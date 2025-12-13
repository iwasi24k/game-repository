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

	constexpr float probability = 0.7f;
	constexpr float downPos = 0.0f;

	for (int i = 0; i < static_cast<int>(m_Blocks.size()); ++i) {
		auto block = m_Blocks[indices[i]];
		auto blockScript = block->GetComponent<BlockScript>();

		if (!blockScript || blockScript->IsMoving() != BlockState::Idle)
			continue;

		// 現在の高さから targetY を決定
		float upPos = block->GetTransform().scale.y;

		float targetY = rand_api::chance(probability)
			? downPos   // 下 70%
			: upPos;    // 上 30%

		// すでに targetY にいる場合はスキップ
		if (fabs(block->GetTransform().position.y - targetY) < 0.01f)
			continue;

		blockScript->StartWarning(targetY);

		--moveCount;
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

float BlockManager::GetBlockHeightAt(const math::transform<math::vector3f>& transform) {
	float maxHeight = 0.0f;

	for (auto& block : m_Blocks) {
		auto& pos = block->GetTransform().position;
		auto& scale = block->GetTransform().scale;

		// キャラクター位置がブロックのXZ範囲に入っているか
		if (transform.position.x + transform.scale.x / 2.2 >= pos.x - scale.x / 2 && transform.position.x - transform.scale.x / 2.2 <= pos.x + scale.x / 2 &&
			transform.position.z + transform.scale.z / 2.2 >= pos.z - scale.z / 2 && transform.position.z - transform.scale.z / 2.2 <= pos.z + scale.z / 2) {
			// 最大の高さを取得（複数ブロック重なっても安全）
			maxHeight = std::max(maxHeight, pos.y);
		}
	}
	return maxHeight;
}
