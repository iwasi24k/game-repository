//==============================================================================
// File        : ResultScene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-1-22
// Last Update : 2025-1-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ResultScene.h"

#include "SceneManager.h"
#include "InputMouse.h"
#include "Scene/Title/TitleScene.h"
#include "Prefab/CameraPrefab.h"
#include "Prefab/Result/ResultBgPrefab.h"

using namespace Framework;

bool ResultScene::SceneInitialize()
{
	CameraPrefab cameraPrefab;
	cameraPrefab.Create(GetGameObjectManager());

	ResultBgPrefab resultBgPrefab;
	resultBgPrefab.Create(GetGameObjectManager());

    return true;
}

void ResultScene::SceneFinalize()
{
}

void ResultScene::SceneUpdate()
{
	if (InputMouse::GetInstance().IsMouseClicked(MB::Left)) {
		SceneManager::GetInstance().LoadScene(std::make_unique<TitleScene>());
	}
}
