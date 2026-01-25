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
#include "Global/GlobalGameData.h"

using namespace Framework;

void CombatProcessing::Start() {
	m_AttackTimer = 0.0f;
	m_IsAttacking = false;
}

void CombatProcessing::Update() {
	m_AttackTimer += Timer::GetInstance().GetDeltaTime();
	if (!m_IsAttacking) return;

	m_AttackTimer = 0.0f;
	m_IsAttacking = false;
	m_HitPoint--;

	if(m_HitPoint <= 0) {
		m_HitPoint = 0;
		if (GetOwner()->GetTag() == "Player") {
			//  Player destruction handling. Currently not implemented.
			Global::GlobalGameData::GetInstance().SetGameFinished(true);
		}
		else {
			GetOwner()->GetComponent<EnemyRespawn>()->Spawn();
			m_HitPoint = m_MaxHitPoint;
			m_AttackTimer = -1.5f;
		}
	}
}

void CombatProcessing::Attack() {
	m_IsAttacking = TryAttack();
}

bool CombatProcessing::TryAttack() {
	if (m_AttackTimer >= m_AttackCooldown) {
		return true; 
	}
	return false;
}