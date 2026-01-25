//==============================================================================
// File        : TimerPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef TIMER_PREFAB_H
#define TIMER_PREFAB_H

#include "Prefab.h"
#include "GameObjectManager.h"

class TimerPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override;
	void Configure(Framework::GameObject* obj) override;
};

#endif // TIMER_PREFAB_H