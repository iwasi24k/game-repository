//==============================================================================
// File        : EnemyScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "EnemyScript.h"
#include "GameObject.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/CameraComponent/TopDownCamera.h"
#include "Framework/Core/Timer.h"
#include "Renderer.h"
#include "ManagerHub.h"
#include "Manager/BlockManager.h"

using namespace Framework;

void EnemyScript::Start() {
    m_SideMoveTimer = rand_api::real(0.0f, m_SideMoveInterval);

    m_IsSideMove = false;
    m_CurrentSideWeight = 0.0f;
}

void EnemyScript::Update() {
    auto rb = GetOwner()->GetComponent<Rigidbody>();
    auto& transform = GetOwner()->GetTransform();
    auto pos = transform.position;
    auto player = FindObject("Player");

    if (!rb || !player) return;

    float dt = Timer::GetInstance().GetDeltaTime();

    auto toPlayer = player->GetTransform().position - pos;
    toPlayer.y = 0.0f;

    float distance = toPlayer.length();
    if (distance > 0.001f) toPlayer.normalize();

    auto forward = ComputeForwardMovement(toPlayer, distance);
    auto side = ComputeSideMovement(toPlayer, distance);
    auto separation = ComputeSeparation(pos);

    auto finalVelocity = forward + side + separation;
    rb->SetVelocity({ finalVelocity.x, 0.0f, finalVelocity.z });

    UpdatePositionY(player, dt);
}

void EnemyScript::UpdatePositionY(GameObject* player, float dt) {
    auto& transform = GetOwner()->GetTransform();

    float targetY = (player->GetTransform().position.y > 2.0f ? 3.0f : 0.5f) + 5.0f;

    transform.position.y = std::lerp(transform.position.y, targetY, 1.0f * dt);
}

math::vector3f EnemyScript::ComputeForwardMovement(const math::vector3f& toPlayer, float distance) {
    if (distance <= m_StopRadius) return { 0,0,0 };
    math::vector3f forward = toPlayer;
    forward.normalize();

    float t = std::clamp((distance - m_StopRadius) / (m_SlowRadius - m_StopRadius), 0.0f, 1.0f);
    float speed = m_MaxSpeed * std::max(t, 0.2f);

    return forward * speed;
}

math::vector3f EnemyScript::ComputeSideMovement(const math::vector3f& toPlayer, float distance) {
    m_SideMoveTimer -= Timer::GetInstance().GetDeltaTime();
    if (m_SideMoveTimer <= 0.0f) {
        m_IsSideMove = !m_IsSideMove;
        m_SideMoveTimer = m_IsSideMove ? m_SideMoveDuration : m_SideMoveInterval;

        if (m_IsSideMove) {
            m_SideDir = (rand() % 2 == 0) ? 1 : -1;
        }
    }

    if (!m_IsSideMove || distance > m_SlowRadius) return { 0,0,0 };

    math::vector3f side = { -toPlayer.z * (float)m_SideDir, 0.0f, toPlayer.x * (float)m_SideDir };
    side.normalize();
    return side * m_MaxSpeed * m_SideWeight;
}

math::vector3f EnemyScript::ComputeSeparation(const math::vector3f& pos) {
    math::vector3f separation{ 0,0,0 };
    auto enemies = FindObjects("Enemy");

    for (auto& e : enemies) {
        if (e == GetOwner()) continue;

        auto diff = pos - e->GetTransform().position;
        diff.y = 0.0f;

        float d = diff.length();
        if (d < 0.001f || d > m_EnemyAvoidRadius) continue;

        diff.normalize();
        separation += diff * (1.0f - d / m_EnemyAvoidRadius);
    }

    separation *= m_EnemyAvoidPower;
    return separation;
}