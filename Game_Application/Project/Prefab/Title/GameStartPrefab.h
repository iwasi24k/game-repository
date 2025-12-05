//==============================================================================
// File        : GameStartPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef GAME_START_PREFAB_H
#define GAME_START_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class GameStartPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // GAME_START_PREFAB_H