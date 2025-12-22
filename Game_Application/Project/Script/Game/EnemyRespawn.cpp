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

	m_Timer += Timer::GetInstance().GetDeltaTime();
	float t = std::clamp(m_Timer, 0.0f, 1.0f);
	float size = std::lerp(0.5f, 0.0f, t);
	GetOwner()->GetTransform().scale = math::vector3f(size, size, size);
	
	if (size > 0.01f) return;

	GetOwner()->GetTransform().scale = math::vector3f(0.5f, 0.5f, 0.5f);
	
	float range = 20.0f;
	math::vector3f pos = math::zero<math::vector3f>();
	pos.x = rand_api::real(-range, range);
	pos.y = 15.0f;
	pos.z = rand_api::real(-range, range);
	GetOwner()->GetTransform().position = pos;
	m_IsSpawn = false;
}
