//==============================================================================
// File        : Rigidbody.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "../../Core/Timer.h"

using namespace Framework;

void Rigidbody::AddForce(const math::vector3f& force) {
    m_Acceleration += force / m_Mass;
}

void Rigidbody::Update() {
    if (!IsEnabled()) {
        return;
    }
    float deltaTime = Timer::GetInstance().GetDeltaTime();
    // 重力の適用
    if (m_UseGravity) {
        m_Velocity.y += m_Gravity * deltaTime;
    }
    // 速度の更新
    m_Velocity += m_Acceleration * deltaTime;
    // 空気抵抗の適用
    if (m_Drag > 0.0f) {
        m_Velocity -= m_Velocity * m_Drag * deltaTime;
    }

	math::vector3f nextPosition = GetOwner()->GetTransform().position + m_Velocity * deltaTime;
    // 位置の更新
    GetOwner()->GetTransform().position = nextPosition;
    // 加速度のリセット
    m_Acceleration = math::zero<math::vector3f>();
}

void Rigidbody::AddPosition(const math::vector3f& p) {
    GetOwner()->GetTransform().position += p;
}

void Rigidbody::ZeroVelocityOnAxis(const math::vector3f& push) {
    // 押し戻しがある軸だけ速度ゼロ
    if (push.x != 0) m_Velocity.x = 0;
    if (push.y != 0) m_Velocity.y = 0;
    if (push.z != 0) m_Velocity.z = 0;
}