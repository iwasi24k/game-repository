//==============================================================================
// File        : CameraPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "CameraPrefab.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Components/CameraComponent/TopDownCamera.h"

using namespace Framework;

GameObject* CameraPrefab::Create(GameObjectManager* mgr) {
    GameObject* cameraObject = mgr->CreateObject("MainCamera");
    cameraObject->AddComponent<TopDownCamera>();
    Configure(cameraObject);
    return cameraObject;
}

void CameraPrefab::Configure(GameObject* obj) {
    auto cameraComp = obj->GetComponent<TopDownCamera>();

    TopDownCameraConfig cameraConfig;
    cameraConfig.targetTag = "Player";
    cameraConfig.height = 7.0f;
    cameraConfig.distance = 10.0f;
    cameraConfig.smooth = 100.0f;

    cameraComp->Configure(cameraConfig);
}
