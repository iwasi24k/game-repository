//==============================================================================
// File        : CombatProcessing.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-22
// Last Update : 2025-12-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef COMBAT_PROCESSING_H
#define COMBAT_PROCESSING_H

#include "GameBehaviour.h"
#include "GameObject.h"

class CombatProcessing : public Framework::GameBehaviour {
private:
	int m_MaxHitPoint = 1;
	int m_HitPoint = 0;
	bool m_IsAttacking = false;
	float m_AttackTimer = 0.0f;
	float m_AttackCooldown = 1.0f;

public:
	void Start() override;
	void Update() override;

	void Attack();
	bool TryAttack();

	void SetAttackCooldown(float cooldown) { m_AttackCooldown = cooldown; }
	void SetHitPoint(int hp) { 
		m_MaxHitPoint = hp;
		m_HitPoint = hp; 
	}
	int GetHitPoint() const { return m_HitPoint; }
};

#endif // COMBAT_PROCESSING_H