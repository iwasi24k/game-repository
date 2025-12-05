//==============================================================================
// File        : TitleCameraPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "TitleCameraPrefab.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Script/Title/TitleCamera.h"

using namespace Framework;

GameObject* TitleCameraPrefab::Create(GameObjectManager* mgr) {
    GameObject* cameraObject = mgr->CreateObject("MainCamera");
    cameraObject->AddComponent<TitleCamera>();
    Configure(cameraObject);
    return cameraObject;
}

void TitleCameraPrefab::Configure(GameObject* obj) {
    auto cameraComp = obj->GetComponent<TitleCamera>();

    TitleCameraConfig cameraConfig;
	cameraConfig.distance = 40.0f;
    cameraConfig.yaw = IX_PI / 4.0f;
	cameraConfig.pitch = -0.25f;

    cameraComp->Configure(cameraConfig);
}
