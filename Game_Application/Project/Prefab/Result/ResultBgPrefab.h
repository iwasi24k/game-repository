//==============================================================================
// File        : ResultBgPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-1-22
// Last Update : 2025-1-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef RESULT_BG_PREFAB_H
#define RESULT_BG_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class ResultBgPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // RESULT_BG_PREFAB_H