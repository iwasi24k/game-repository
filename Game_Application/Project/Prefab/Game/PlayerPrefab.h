//==============================================================================
// File        : PlayerPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef PLAYER_PREFAB_H
#define PLAYER_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class PlayerPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override; 
	void Configure(Framework::GameObject* obj) override;
};

#endif // PLAYER_PREFAB_H