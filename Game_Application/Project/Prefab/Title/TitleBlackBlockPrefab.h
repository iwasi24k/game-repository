//==============================================================================
// File        : TitleBlackBlockPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef BLACK_BLOCK_PREFAB_H
#define BLACK_BLOCK_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class TitleBlackBlockPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // BLACK_BLOCK_PREFAB_H