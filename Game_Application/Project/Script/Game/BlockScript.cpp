//==============================================================================
// File        : BlockScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-30
// Last Update : 2025-11-30
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "BlockScript.h"
#include "Framework/Core/Timer.h"
#include "GameObject.h"
#include "Components/RenderComponent/ModelComponent.h"

using namespace Framework;

void BlockScript::Start() {
	m_DefaultColor = m_Material.Diffuse;
}

void BlockScript::Update() {
	if (m_State == BlockState::Idle) return;

	float dt = Timer::GetInstance().GetDeltaTime();
	auto& t = GetOwner()->GetTransform();
	float sinValue = 0.0f;
	math::vector4f color{};
	auto modelComp = GetOwner()->GetComponent<ModelComponent>();
	if (!modelComp) return;

	switch (m_State) {
	case BlockState::Warning:
		if (!m_IsWarning) {
			m_State = BlockState::Moving;
			return;
		}

		m_WarningTimer += dt;

		sinValue = (sinf(m_WarningTimer * 8.0f) * 0.5f + 0.5f);
		color = math::lerp(m_DefaultColor, m_WarningColor, sinValue);
		m_Material.Diffuse = color;
		modelComp->SetMaterial(m_Material);

		if (m_WarningTimer >= m_WarningTime) {
			m_State = BlockState::Moving;
			m_WarningTimer = 0.0f;
			m_Material.Diffuse = m_DefaultColor;
			modelComp->SetMaterial(m_Material);
		}
		return;
	case BlockState::Moving:

		m_CurrentY = t.position.y;

		// 一定速度で移動する実装（符号を保ちつつ step ずつ移動）
		float distance = m_TargetY - m_CurrentY;
		float dir = (distance > 0.0f) ? 1.0f : -1.0f;
		float step = m_MoveSpeed * dt; // m_MoveSpeed は「単位/秒」
		float newY = m_CurrentY + dir * step;

		if (fabs(newY - m_TargetY) < 0.01f) {
			newY = m_TargetY;
			m_State = BlockState::Idle;
			m_WarningTimer = 0.0f;
		}

		m_CurrentY = newY;
		t.position.y = m_CurrentY;
		return;
	}
}
