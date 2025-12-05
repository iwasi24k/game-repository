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
#include "SceneManager.h"
#include "Renderer.h"
#include "ManagerHub.h"
#include "Scene/Game/GameScene.h"
#include "InputKeyboard.h"
#include "Prefab/Title/TitleCameraPrefab.h"
#include "Prefab/Title/TitleLogoPrefab.h"

using namespace Framework;

bool TitleScene::SceneInitialize() {

	TitleCameraPrefab cameraPrefab;
	auto camera = cameraPrefab.Create(GetGameObjectManager());

	GetManagerHub()->AddManager<TitleBlockManager>(std::make_unique<TitleBlockManager>());

	TitleLogoPrefab testPrefab;
	testPrefab.Create(GetGameObjectManager());

	return true;
}

void TitleScene::SceneFinalize() {
}

void TitleScene::SceneUpdate() {
	if (InputKeyboard::GetInstance().IsKeyTriggered(KB::Enter)) {
		SceneManager::GetInstance().LoadScene(std::make_unique<GameScene>());
	}
}
