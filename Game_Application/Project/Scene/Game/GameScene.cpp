//==============================================================================
// File        : GameScene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "GameScene.h"

#include "Prefab/CameraPrefab.h"
#include "Prefab/Game/PlayerPrefab.h"
#include "Prefab/Game/EnemyPrefab.h"

#include "Script/Game/Manager/BlockManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ManagerHub.h"

using namespace Framework;

bool GameScene::SceneInitialize() {

	CameraPrefab cameraPrefab;
	cameraPrefab.Create(GetGameObjectManager());

	PlayerPrefab playerPrefab;
	playerPrefab.Create(GetGameObjectManager());

	EnemyPrefab enemyPrefab;
	enemyPrefab.Create(GetGameObjectManager());
	enemyPrefab.Create(GetGameObjectManager())->GetTransform().position.x = 20.0f;

	GetManagerHub()->AddManager<BlockManager>(std::make_unique<BlockManager>());

    return true;
}

void GameScene::SceneFinalize(){
}

void GameScene::SceneUpdate(){
	
}
