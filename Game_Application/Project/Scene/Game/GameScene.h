//==============================================================================
// File        : GameScene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "Script/Game/Manager/BlockManager.h"

class GameScene : public Framework::Scene {
private:
	BlockManager m_BlockManager;

public:
	bool SceneInitialize() override;
	void SceneFinalize() override;
	void SceneUpdate() override;

	BlockManager& GetBlockManager() { return m_BlockManager; }
};

#endif // GAME_SCENE_H
