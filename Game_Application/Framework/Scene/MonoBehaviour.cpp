//==============================================================================
// File        : MonoBehaviour.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-03
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "MonoBehaviour.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

using namespace Framework;

Scene* MonoBehaviour::GetScene() {
    return SceneManager::GetInstance().GetCurrentScene();
}

ManagerHub* MonoBehaviour::GetManagerHub() {
    return SceneManager::GetInstance().GetCurrentScene()->GetManagerHub();
}
