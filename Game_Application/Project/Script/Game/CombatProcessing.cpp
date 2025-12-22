//==============================================================================
// File        : CombatProcessing.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-22
// Last Update : 2025-12-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "CombatProcessing.h"
#include "Timer.h"
#include "EnemyRespawn.h"

using namespace Framework;

void CombatProcessing::Start() {
	m_AttackTimer = 0.0f;
	m_IsAttack = false;
}

void CombatProcessing::Update() {
	m_AttackTimer += Timer::GetInstance().GetDeltaTime();
	if (!m_IsAttack) return;

	m_AttackTimer = 0.0f;
	m_IsAttack = false;
	m_HitPoint--;

	if(m_HitPoint <= 0) {
		m_HitPoint = 0;
		if (GetOwner()->GetTag() == "Player") {

		}
		else {
			GetOwner()->GetComponent<EnemyRespawn>()->Spawn();
			m_HitPoint = 2;
			m_AttackTimer = -1.5f;
		}
	}
}

void CombatProcessing::Attack() {
	if (m_AttackTimer < 1.0f)
		m_IsAttack = false;
	else
		m_IsAttack = true;
}
