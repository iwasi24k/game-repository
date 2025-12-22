//==============================================================================
// File        : PlayerSkillScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-22
// Last Update : 2025-12-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "PlayerSkillScript.h"
#include "Timer.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "DebugTool.h"
#include "InputMouse.h"

using namespace Framework;

void PlayerSkillScript::Start() {
	m_GameObject = FindObject("Player");
}

void PlayerSkillScript::Update() {
	if (!m_GameObject) return;

	switch (m_SkillState) {
	case PlayerSkillState::Idle:
		GetOwner()->GetTransform().position = m_GameObject->GetTransform().position;

		if (InputMouse::GetInstance().IsMouseClicked(MB::Left)) {
			SkillActivation();
		}

		if (m_IsActivation) {
			m_IsActivation = false;
			m_IsAction = true;
			m_SkillState = PlayerSkillState::Action;
		}
		break;

	case PlayerSkillState::Action:
		PlayerActionAnimation();
		if (!m_IsAction) {
			m_SkillState = PlayerSkillState::Idle;
		}
		break;
	}
}

void PlayerSkillScript::SkillActivation() {
	m_IsActivation = true;
}

void PlayerSkillScript::OnTriggerEnter(GameObject* other) {
	if (other->GetTag() == "Enemy") {
		
	}
}

void PlayerSkillScript::PlayerActionAnimation() {
	auto modelComp = GetOwner()->GetComponent<ModelComponent>();
	if (!modelComp) MSG_ERRF(L"not found [ModelComponent]");

	float dt = Timer::GetInstance().GetDeltaTime();

	auto& scale = GetOwner()->GetTransform().scale;
	float current = scale.y;

	// --- すでに最大値に達している場合は即リセット ---
	if (current >= kActionMaxScale) {
		m_IsAction = false;
		auto& pos = GetOwner()->GetTransform().position;
		pos = m_GameObject->GetTransform().position;
		scale = { 0.25f, 0.25f, 0.25f };

		math::vector4f reset = kDefaultColor;
		modelComp->SetDiffuse(reset);
		return;
	}

	current += kActionSpeed * dt;
	current = std::min(current, kActionMaxScale);
	scale = { 5.0f, current , 5.0f };

	float t = current / kActionMaxScale; // 0 -> 1
	float alpha = std::lerp(0.75f, 0.0f, t); // 1.0 -> 0.0

	math::vector4f diffuse = { kDefaultColor.x, kDefaultColor.y, kDefaultColor.z, alpha };
	modelComp->SetDiffuse(diffuse);
}
