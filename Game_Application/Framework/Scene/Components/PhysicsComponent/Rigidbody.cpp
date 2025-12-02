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

void Rigidbody::AddImpulse(const math::vector3f& impulse) {
    m_Velocity += impulse / m_Mass;
}

void Rigidbody::AddForce(const math::vector3f& force) {
    m_Acceleration += force / m_Mass;
}

void Rigidbody::FixedUpdate() {
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

    // 加速度のリセット
    m_Acceleration = math::zero<math::vector3f>();
}