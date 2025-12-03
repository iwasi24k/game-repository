//==============================================================================
// File        : ObjectManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-03
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ObjectManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"

using namespace Framework;

GameObjectManager* ObjectManager::GetGameObjectManager() {
    return SceneManager::GetInstance().GetCurrentScene()->GetGameObjectManager();
}
