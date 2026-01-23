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
#include "Script/Game/Manager/EnemyManager.h"
#include "Prefab/Game/SkillPrefab.h"
#include "Script/Game/PlayerSkillScript.h"
#include "Global/GlobalGameData.h"
#include <Scene/Title/TitleScene.h>

using namespace Framework;

bool GameScene::SceneInitialize() {
	Global::GlobalGameData::GetInstance().SetGameFinished(false);

	CameraPrefab cameraPrefab;
	cameraPrefab.Create(GetGameObjectManager());

	PlayerPrefab playerPrefab;
	playerPrefab.Create(GetGameObjectManager());

	SkillPrefab skillPrefab;
	auto playerSkill = skillPrefab.Create(GetGameObjectManager());
	playerSkill->AddComponent<PlayerSkillScript>();

	GetManagerHub()->AddManager<EnemyManager>(std::make_unique<EnemyManager>());

	GetManagerHub()->AddManager<BlockManager>(std::make_unique<BlockManager>());

    return true;
}

void GameScene::SceneFinalize(){
}

void GameScene::SceneUpdate(){
	if (Global::GlobalGameData::GetInstance().IsGameFinished()) {
		SceneManager::GetInstance().LoadScene(std::make_unique<TitleScene>());
	}
}
