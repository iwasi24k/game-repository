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
#include "Components/RenderComponent/ModelComponent.h"
#include "DebugTool.h"

using namespace Framework;

void EnemySkillScript::Start() {
	float time = rand_api::real(4.0f, 8.0f);
	m_InitialTime = time;
}

void EnemySkillScript::Update() {
	if (!m_GameObject) return;

	if (m_InitialTime >= 0.0f) {
		m_InitialTime -= Timer::GetInstance().GetDeltaTime();
		return;
	}
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
		EnemyActionAnimation();
		if (!m_IsAction) {
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

	m_MoveDir = math::normalize(m_TargetPosition - m_ActionPosition);
}

void EnemySkillScript::OnTriggerEnter(GameObject* other) {
	if (other->GetTag() == "Player" || other->GetTag() == "Block") {
		m_IsHit = true;
	}
}

void EnemySkillScript::EnemyMoveAnimation() {
	float dt = Timer::GetInstance().GetDeltaTime();

	auto& pos = GetOwner()->GetTransform().position;

	pos += m_MoveDir * kMoveSpeed * dt;
}

void EnemySkillScript::EnemyActionAnimation() {
	auto modelComp = GetOwner()->GetComponent<ModelComponent>();
	if (!modelComp) MSG_ERRF(L"not found [ModelComponent]");

	float dt = Timer::GetInstance().GetDeltaTime();

	auto& scale = GetOwner()->GetTransform().scale;
	float current = scale.x;

	// --- すでに最大値に達している場合は即リセット ---
	if (current >= kActionMaxScale) {
		m_IsAction = false;
		auto& pos = GetOwner()->GetTransform().position;
		pos = m_GameObject->GetTransform().position;
		scale = { 0.25f, 0.25f, 0.25f };

		math::vector4f reset = { 1.0f, 1.0f, 1.0f, 1.0f };
		modelComp->SetDiffuse(reset);
		m_IsHit = false;
		return;
	}

	current += kActionSpeed * dt;
	current = std::min(current, kActionMaxScale);
	scale = { current, current , current };

	float alpha = 1.0f - (current / kActionMaxScale);
	alpha = std::clamp(alpha, 0.0f, 1.0f);

	math::vector4f diffuse = { 1.0f, 1.0f, 1.0f, alpha };
	modelComp->SetDiffuse(diffuse);
}
