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
	int m_HitPoint = 0;
	bool m_IsAttack = false;
	float m_AttackTimer = 0.0f;

public:
	void Start() override;
	void Update() override;

	void Attack();

	void SetHitPoint(int hp) { m_HitPoint = hp; }
	int GetHitPoint() const { return m_HitPoint; }
};

#endif // COMBAT_PROCESSING_H