//==============================================================================
// File        : SkillPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-18
// Last Update : 2025-12-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef SKILL_PREFAB_H
#define SKILL_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class SkillPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // SKILL_PREFAB_H