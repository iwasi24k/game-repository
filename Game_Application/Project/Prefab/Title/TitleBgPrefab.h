//==============================================================================
// File        : TitleBgPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef TITLE_BG_PREFAB_H
#define TITLE_BG_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class TitleBgPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // TITLE_BG_PREFAB_H