//==============================================================================
// File        : MonoBehaviour.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-03
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "GameBehaviour.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

using namespace Framework;

Scene* GameBehaviour::GetScene() {
    return SceneManager::GetInstance().GetCurrentScene();
}

ManagerHub* GameBehaviour::GetManagerHub() {
    return SceneManager::GetInstance().GetCurrentScene()->GetManagerHub();
}
