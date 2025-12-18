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
#include "Prefab/Game/SkillPrefab.h"
#include "Script/Game/EnemySkillScript.h"

using namespace Framework;

void EnemyManager::Create() {
	auto gameObject = GetGameObjectManager();

	EnemyPrefab enemyPrefab;
	SkillPrefab enemySkill;

	for (int i = 0; i < kEnemyMax; ++i) {
		auto obj = enemyPrefab.Create(gameObject);
		auto enemy = obj->GetComponent<EnemyRespawn>();
		enemy->Spawn();
		auto skillObj = enemySkill.Create(gameObject);
		auto skill = skillObj->AddComponent<EnemySkillScript>();
		skill->SetEnemy(obj);
	}

}

void EnemyManager::Update() {
}