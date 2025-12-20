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
	float frame = rand_api::real(240.0f, 360.0f);
	m_InitialFrame = frame;
}

void EnemySkillScript::Update() {
	if (!m_GameObject) return;

	if (m_InitialFrame >= 0.0f) {
		m_InitialFrame--;
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
	float speed = 3.0f;
	float dt = Timer::GetInstance().GetDeltaTime();

	auto& pos = GetOwner()->GetTransform().position;

	pos += m_MoveDir * speed * dt;
}

void EnemySkillScript::EnemyActionAnimation() {
	float speed = 2.5f;
	float dt = Timer::GetInstance().GetDeltaTime();

	auto& scale = GetOwner()->GetTransform().scale;
	float maxScale = 3.0f;
	float current = scale.x;

	// --- すでに最大値に達している場合は即リセット ---
	if (current >= maxScale) {
		m_IsAction = false;
		auto& pos = GetOwner()->GetTransform().position;
		pos = m_GameObject->GetTransform().position;
		scale = { 0.25f, 0.25f, 0.25f };

		auto modelComp = GetOwner()->GetComponent<ModelComponent>();
		math::vector4f reset = { 1.0f, 1.0f, 1.0f, 1.0f };
		modelComp->SetDiffuse(reset);
		m_IsHit = false;
		return;
	}

	current += speed * dt;
	current = std::min(current, maxScale);
	scale = { current, current , current };

	float alpha = 1.0f - (current / maxScale);
	alpha = std::clamp(alpha, 0.0f, 1.0f);

	auto modelComp = GetOwner()->GetComponent<ModelComponent>();
	if (!modelComp) MSG_ERRF(L"not found [ModelComponent]");
	math::vector4f diffuse = { 1.0f, 1.0f, 1.0f, alpha };
	modelComp->SetDiffuse(diffuse);
}
