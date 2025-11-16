//==============================================================================
// File        : Component.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Component.h"

#include "SceneManager.h"
#include "GameObjectManager.h"

using namespace Framework;

GameObject* Component::FindObject(const std::string& tag) {
    return SceneManager::GetInstance().GetCurrentScene()->GetGameObjectManager()->FindObject(tag);
}
