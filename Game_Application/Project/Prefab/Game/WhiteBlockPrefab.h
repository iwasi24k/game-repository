//==============================================================================
// File        : WhiteBlockPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef WHITE_BLOCK_PREFAB_H
#define WHITE_BLOCK_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class WhiteBlockPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // WHITE_BLOCK_PREFAB_H