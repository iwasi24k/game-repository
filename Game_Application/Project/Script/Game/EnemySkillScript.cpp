//==============================================================================
// File        : EnemySkillScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-18
// Last Update : 2025-12-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "EnemySkillScript.h"
#include "Timer.h"

using namespace Framework;

void EnemySkillScript::Start() {

}

void EnemySkillScript::Update() {
	if (!m_GameObject) return;

	switch (m_SkillState) {
	case EnemySkillState::Idle:
		GetOwner()->GetTransform().position = m_GameObject->GetTransform().position;

		if (rand_api::chance(1.0f)) {
			SkillActivation();
		}

		if (m_IsActivation) {
			m_IsActivation = false;
			m_SkillState = EnemySkillState::Move;
		}
		break;

	case EnemySkillState::Move:
		EnemyMoveAnimation();

		if (m_IsHit) {
			m_IsHit = false;
			m_IsAction = true;
			m_SkillState = EnemySkillState::Action;
		}
		break;

	case EnemySkillState::Action:
		if (m_IsAction) {
			m_SkillState = EnemySkillState::Idle;
		}
		break;
	}
}

void EnemySkillScript::SetEnemy(GameObject* enemy) {
	m_GameObject = enemy;
}

void EnemySkillScript::SkillActivation() {
	m_IsActivation = true;
	m_ActionPosition = GetOwner()->GetTransform().position;
	m_TargetPosition = FindObject("Player")->GetTransform().position;
}

void EnemySkillScript::OnTriggerEnter(GameObject* other) {
	if (other->GetTag() == "Player" || other->GetTag() == "Block") {
		m_IsHit = true;
	}
}

void EnemySkillScript::EnemyMoveAnimation() {
	float speed = 2.0f;
	float dt = Timer::GetInstance().GetDeltaTime();

	auto& pos = GetOwner()->GetTransform().position;

	math::vector3f dir = m_TargetPosition - pos;
	float length = math::length(dir);

	if (length < 0.01f) {
		m_IsHit = true;
		pos = m_TargetPosition;
		return;
	}
	dir = math::normalize(dir);
	pos += dir * speed * dt;
}
