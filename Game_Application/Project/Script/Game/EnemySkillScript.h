//==============================================================================
// File        : EnemySkillScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-18
// Last Update : 2025-12-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef ENEMY_SKILL_SCRIPT_H
#define ENEMY_SKILL_SCRIPT_H

#include "GameBehaviour.h"
#include "GameObject.h"

class EnemySkillScript : public Framework::GameBehaviour {
private:
	enum class EnemySkillState { Idle, Move, Action };

	EnemySkillState m_SkillState = EnemySkillState::Idle;
	Framework::GameObject* m_GameObject = nullptr;

	math::vector3f m_ActionPosition = math::zero<math::vector3f>();
	math::vector3f m_TargetPosition = math::zero<math::vector3f>();
	math::vector3f m_MoveDir = math::zero<math::vector3f>();

	bool m_IsActivation = false;
	bool m_IsAction = false;
	bool m_IsHit = false;

	float m_InitialTime = 6.0f;

	static constexpr float kMoveSpeed = 3.0f;
	static constexpr float kActionSpeed = 2.5f;
	static constexpr float kActionMaxScale = 3.0f;

public:
	void Start() override;
	void Update() override;

	void SetEnemy(Framework::GameObject* enemy);
	void SkillActivation();

	void OnTriggerEnter(Framework::GameObject* other) override;

private:
	void EnemyMoveAnimation();
	void EnemyActionAnimation();
};

#endif // ENEMY_RESPAWN_H