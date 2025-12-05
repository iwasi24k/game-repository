//==============================================================================
// File        : TitleWhiteBlockPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef WHITE_BLOCK_PREFAB_H
#define WHITE_BLOCK_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class TitleWhiteBlockPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // WHITE_BLOCK_PREFAB_H