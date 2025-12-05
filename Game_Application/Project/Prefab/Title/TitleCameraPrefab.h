//==============================================================================
// File        : TitleCameraPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef TITLE_CAMERA_PREFAB_H
#define TITLE_CAMERA_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class TitleCameraPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // TITLE_CAMERA_PREFAB_H