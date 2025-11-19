//==============================================================================
// File        : BlockPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef BLOCK_PREFAB_H
#define BLOCK_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class BlockPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // BLOCK_PREFAB_H