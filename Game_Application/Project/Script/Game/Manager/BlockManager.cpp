#include "pch.h"
#include "BlockManager.h"
#include "Prefab/Game/WhiteBlockPrefab.h"
#include "Prefab/Game/BlackBlockPrefab.h"

using namespace Framework;

void BlockManager::Create(GameObjectManager* mgr) {
    m_GameObjectManager = mgr;

	WhiteBlockPrefab whiteBlockPrefab;
	BlackBlockPrefab blackBlockPrefab;

	// チェス盤のようにブロックを配置
	for (int x = -m_BlockCountX / 2; x <= m_BlockCountX / 2; ++x) {
		for (int z = -m_BlockCountZ / 2; z <= m_BlockCountZ / 2; ++z) {
			Prefab& blockPrefab = ((x + z) % 2 == 0) ? static_cast<Prefab&>(whiteBlockPrefab) : static_cast<Prefab&>(blackBlockPrefab);
			auto block = blockPrefab.Create(m_GameObjectManager);
			block->GetTransform().position = math::vector3f(static_cast<float>(x * 2.4f), 0.0f, static_cast<float>(z * 2.4f));
			m_Blocks.push_back(block);
		}
	}
}

void BlockManager::Update() {
	for (const auto& block : m_Blocks) {
		auto position = block->GetTransform().position;
		position.y += (rand() % 2 == 0 ? 1.0f : -1.0f);
		block->GetTransform().position = position;
	}
}
