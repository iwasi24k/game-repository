//==============================================================================
// File        : PlayerHpPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef PLAYER_HP_PREFAB_H
#define PLAYER_HP_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class PlayerHpPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // PLAYER_HP_PREFAB_H