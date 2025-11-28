//==============================================================================
// File        : TopDownCamera.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
//
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
    if (!IsEnabled() || m_TargetTag == "None" || !m_TargetObject)
        return;

    auto& transform = GetOwner()->GetTransform();
    math::vector3f targetPos = m_TargetObject->GetTransform().position;

    // --- m_Focusだけターゲットに遅れて追従 ---
    math::vector3f delta = targetPos - m_Focus;
    m_Focus += delta * Timer::GetInstance().GetDeltaTime() * m_Smooth;

    // --- カメラ位置は m_Focus + オフセットで即座に決定 ---
    math::vector3f offset(0.0f, m_Height, -m_Distance);

    // Yawで横回転、Pitchで上からの角度
    math::matrix rot = math::matrix::RotationX(m_Rotation.x) * math::matrix::RotationY(m_Rotation.y);
    math::vector3f camPos = m_Focus + rot.TransformVector(offset);

    transform.position = camPos; // カメラは遅れず追従

    // --- 注視点は m_Focus ---
    UpdateView(camPos, m_Focus);
}




//void TopDownCamera::Update() {
//	if (!IsEnabled() || m_TargetTag == "None" || !m_TargetObject) {
//		return;
//	}
//
//	const math::vector3f& targetPos = m_TargetObject->GetTransform().position;
//
//	// --- 基本オフセット（真上 + 後ろ）---
//	math::vector3f offset(0.0f, m_Height, -m_Distance);
//
//	// --- Yaw と Pitch を適用 ---
//	math::matrix rot =
//		math::matrix::RotationX(m_Rotation.x) *
//		math::matrix::RotationY(m_Rotation.y);
//
//	offset = rot.TransformVector(offset);
//
//	// --- 目標位置 ---
//	math::vector3f desiredPosition = targetPos + offset;
//
//	auto& transform = GetOwner()->GetTransform();
//	auto current = transform.position;
//
//	// スムーズ追従
//	math::vector3f newPos =
//		math::lerp(current, desiredPosition, Timer::GetInstance().GetDeltaTime() * m_Smooth);
//
//	transform.position = newPos;
//
//	// --- 注視点はターゲット固定 ---
//	UpdateView(newPos, targetPos);
//}
