//==============================================================================
// File        : ScorePrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef SCORE_PREFAB_H
#define SCORE_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class ScorePrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // SCORE_PREFAB_H