//==============================================================================
// File        : EnemyPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef ENEMY_PREFAB_H
#define ENEMY_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class EnemyPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // ENEMY_PREFAB_H