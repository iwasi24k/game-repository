//==============================================================================
// File        : TitleScene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "TitleScene.h"

#include "Script/Title/Manager/TitleBlockManager.h"
#include "Script/Title/Manager/BgBlockManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ManagerHub.h"
#include "Scene/Game/GameScene.h"
#include "InputMouse.h"
#include "Prefab/Title/TitleCameraPrefab.h"
#include "Prefab/Title/TitleLogoPrefab.h"
#include "Prefab/Title/GameStartPrefab.h"
#include "Prefab/Title/TitleBgPrefab.h"

using namespace Framework;

bool TitleScene::SceneInitialize() {

	TitleCameraPrefab cameraPrefab;
	auto camera = cameraPrefab.Create(GetGameObjectManager());

	TitleBgPrefab titleBgPrefab;
	titleBgPrefab.Create(GetGameObjectManager());

	GetManagerHub()->AddManager<TitleBlockManager>(std::make_unique<TitleBlockManager>());

	TitleLogoPrefab titlePrefab;
	titlePrefab.Create(GetGameObjectManager());

	GameStartPrefab gameStartPrefab;
	gameStartPrefab.Create(GetGameObjectManager());

	GetManagerHub()->AddManager<BgBlockManager>(std::make_unique<BgBlockManager>());

	return true;
}

void TitleScene::SceneFinalize() {
}

void TitleScene::SceneUpdate() {
	if (InputMouse::GetInstance().IsMouseClicked(MB::Left)) {
		SceneManager::GetInstance().LoadScene(std::make_unique<GameScene>());
	}
}
