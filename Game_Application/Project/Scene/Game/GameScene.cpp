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

using namespace Framework;

bool GameScene::SceneInitialize() {

	CameraPrefab cameraPrefab;
	cameraPrefab.Create(GetGameObjectManager());

	PlayerPrefab playerPrefab;
	playerPrefab.Create(GetGameObjectManager());

	TestPrefab testPrefab;
	testPrefab.Create(GetGameObjectManager());

    return true;
}

void GameScene::SceneFinalize(){
}

void GameScene::SceneUpdate(){
}
