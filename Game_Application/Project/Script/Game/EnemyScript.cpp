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
    // Initialization code here

}

void EnemyScript::Update() {
    auto rb = GetOwner()->GetComponent<Rigidbody>();
    auto& transform = GetOwner()->GetTransform();
    auto pos = transform.position;
    auto player = FindObject("Player");

    if (!rb || !player) return;

    // ---------- ˆÚ“®•ûŒü ----------
    auto direction = player->GetTransform().position - pos;
    if (direction.length() > 0.001f)
        direction.normalize();
    else
        direction = math::vector3f(0, 0, 0);

    float speed = 3.0f;
    rb->SetVelocity({ direction.x * speed, 0.0f, direction.z * speed });

    // ---------- YÀ•W‚Ì•âŠ® ----------
    float targetY =
        (player->GetTransform().position.y > 2.0f ? 3.0f : 0.0f) + 5.0f;

    float dt = Timer::GetInstance().GetDeltaTime();
    float followSpeed = 1.0f;

    transform.position.y =
        std::lerp(transform.position.y, targetY, followSpeed * dt);
}

