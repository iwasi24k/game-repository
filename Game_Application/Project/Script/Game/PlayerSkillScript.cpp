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
#include "CombatProcessing.h"

using namespace Framework;

void PlayerSkillScript::Start() {
	m_GameObject = FindObject("Player");
}

void PlayerSkillScript::Update() {
	if (!m_GameObject) return;

	switch (m_SkillState) {
	case PlayerSkillState::Idle:
		GetOwner()->GetTransform().position = m_GameObject->GetTransform().position;

		if(m_CoolTime < kMaxCoolTime) {
			m_CoolTime += Timer::GetInstance().GetDeltaTime();
			return;
		}
		if (InputMouse::GetInstance().IsMouseClicked(MB::Left)) {
			SkillActivation();
			m_CoolTime = 0.0f;
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
		other->GetComponent<CombatProcessing>()->Attack();
	}
}

void PlayerSkillScript::PlayerActionAnimation() {
	auto modelComp = GetOwner()->GetComponent<ModelComponent>();
	if (!modelComp) MSG_ERRF(L"not found [ModelComponent]");

	float dt = Timer::GetInstance().GetDeltaTime();

	auto& scale = GetOwner()->GetTransform().scale;
	float current = scale.y;
	float threshold = kActionMaxScale * 0.9f;

	if (current >= threshold) {
		m_IsAction = false;
		auto& pos = GetOwner()->GetTransform().position;
		pos = m_GameObject->GetTransform().position;
		scale = { 0.25f, 0.25f, 0.25f };

		math::vector4f reset = kDefaultColor;
		modelComp->SetDiffuse(reset);
		return;
	}

	current = std::lerp(current, kActionMaxScale, kActionSpeed * dt);

	// scale yŽ²‚Ì‚ÝŠg‘å(cUŒ‚‚ð‘z’è)
	scale = { 5.0f, current , 5.0f };

	float t = current / kActionMaxScale;
	float alpha = std::lerp(1.0f, 0.0f, t);

	math::vector4f diffuse = { kDefaultColor.x, kDefaultColor.y, kDefaultColor.z, alpha };
	modelComp->SetDiffuse(diffuse);
}
