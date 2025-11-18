//==============================================================================
// File        : TopDownCamera.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#include "pch.h"
#include "TopDownCamera.h"
#include "GameObject.h"
#include "../../Core/Timer.h"

using namespace Framework;

void TopDownCamera::Start() {
	// 初期位置設定
	if (m_TargetTag == "None") {
		return;
	}
	m_TargetObject = FindObject(m_TargetTag);
	if (m_TargetObject) {
		GetOwner()->GetTransform().position = m_TargetObject->GetTransform().position + math::vector3f(0.0f, m_Height, -m_Distance);
	}
}

void TopDownCamera::Update() {
	if(!IsEnabled() || m_TargetTag == "None" || !m_TargetObject) {
		return;
	}

	// カメラの位置を計算
	const math::vector3f& targetPosition = m_TargetObject->GetTransform().position;

	math::vector3f desiredPosition = targetPosition + math::vector3f(0.0f, m_Height, -m_Distance);

	auto& transform = GetOwner()->GetTransform();
	auto currentPosition = transform.position;

	// スムーズに追従
	math::vector3f newPosition = math::lerp(currentPosition, desiredPosition, Timer::GetInstance().GetDeltaTime() * m_Smooth);
	transform.position = newPosition;

	math::vector3f targetLookAt = targetPosition;
	m_View = math::matrix::LookAtLH(transform.position, targetLookAt, math::vector3f(0.0f, 1.0f, 0.0f));

	m_ViewProjection = m_View * m_Projection;
}
