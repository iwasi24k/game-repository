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
#include "GameObject.h"

using namespace Framework;

void EnemyRespawn::Start() {
}

void EnemyRespawn::Update() {
	if (!m_IsSpawn) return;
	
	float range = 20.0f;
	math::vector3f pos = math::zero<math::vector3f>();
	pos.x = rand_api::real(-range, range);
	pos.y = 15.0f;
	pos.z = rand_api::real(-range, range);
	GetOwner()->GetTransform().position = pos;
	m_IsSpawn = false;
}
