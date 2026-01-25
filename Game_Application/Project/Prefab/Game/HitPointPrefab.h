//==============================================================================
// File        : HitPointPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef HITPOINT_PREFAB_H
#define HITPOINT_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class HitPointPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // HITPOINT_PREFAB_H