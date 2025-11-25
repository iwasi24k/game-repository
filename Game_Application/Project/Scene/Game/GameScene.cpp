//==============================================================================
// File        : GameScene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "GameScene.h"
#include "Prefab/Game/PlayerPrefab.h"
#include "Prefab/Game/TestPrefab.h"
#include "Prefab/CameraPrefab.h"

#include "Script/Game/Manager/BlockManager.h"

using namespace Framework;

bool GameScene::SceneInitialize() {

	CameraPrefab cameraPrefab;
	cameraPrefab.Create(GetGameObjectManager());

	PlayerPrefab playerPrefab;
	playerPrefab.Create(GetGameObjectManager());

	BlockManager blockManager;
	blockManager.Create(GetGameObjectManager());

	TestPrefab testPrefab;
	testPrefab.Create(GetGameObjectManager());
	auto test = testPrefab.Create(GetGameObjectManager());
	test->GetTransform().position.x *= 3;
	auto tr = test->GetComponent<SpriteComponent>();
	tr->SetColor({ 1.0f, 0.0f, 0.0f, 0.5f });
	tr->SetUV(0.5f, 0.5f, 1.0f, 1.0f);

    return true;
}

void GameScene::SceneFinalize(){
}

void GameScene::SceneUpdate(){
}
