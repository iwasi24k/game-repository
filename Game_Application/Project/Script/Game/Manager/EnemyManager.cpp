//==============================================================================
// File        : EnemyManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "EnemyManager.h"
#include "Framework/Core/Timer.h"
#include "Prefab/Game/EnemyPrefab.h"
#include "Script/Game/EnemyRespawn.h"

using namespace Framework;

void EnemyManager::Create() {
	auto gameObject = GetGameObjectManager();

	EnemyPrefab enemyPrefab;
	for (int i = 0; i < kEnemyMax; ++i) {
		auto obj = enemyPrefab.Create(gameObject);
		auto enemy = obj->GetComponent<EnemyRespawn>();
		enemy->Spawn(10.0f);
	}

}

void EnemyManager::Update() {
}