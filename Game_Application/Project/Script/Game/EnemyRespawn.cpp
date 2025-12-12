//==============================================================================
// File        : EnemyRespawn.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "EnemyRespawn.h"
#include "Framework/Core/Timer.h"

using namespace Framework;

void EnemyRespawn::Start() {
	m_IsSpawn = false;
	m_SpawnTimer = 0.0f;
}

void EnemyRespawn::Update() {
	if (!m_IsSpawn) return;
	m_SpawnTimer -= Timer::GetInstance().GetDeltaTime();
	if (m_SpawnTimer > 0.0f) return;
	
	float range = 10.0f;
	rand_api::real(-range, range);
}
