//==============================================================================
// File        : PhysicsComponentManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "PhysicsComponentManager.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

using namespace Framework;

void PhysicsComponentManager::Start(std::vector<std::unique_ptr<GameObject>>& gameObjects) {

}

void PhysicsComponentManager::Update(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    // ▼ A-B / B-A の二重処理を避ける
    for (size_t i = 0; i < gameObjects.size(); i++) {
        for (size_t j = i + 1; j < gameObjects.size(); j++) {
            auto& a = gameObjects[i];
            auto& b = gameObjects[j];

            auto ca = a->GetComponent<BoxCollider>();
            auto cb = b->GetComponent<BoxCollider>();
            if (!ca || !cb) continue;

            const AABB& A = ca->GetWorldAABB();
            const AABB& B = cb->GetWorldAABB();

            if (!A.Intersect(B))
                continue;

            // ▼ Rigidbody の取得
            auto rbA = a->GetComponent<Rigidbody>();
            auto rbB = b->GetComponent<Rigidbody>();

            // ▼ 押し戻しベクトルを計算
            math::vector3f push;
            if (AABB::ComputePush(A, B, push)) {
                // ▼ Rigidbody が片方だけ → そちらだけ押す
                if (rbA && !rbB) {
                    rbA->AddPosition(push);
                    rbA->ZeroVelocityOnAxis(push);
                }
                else if (!rbA && rbB) {
                    rbB->AddPosition(-push);
                    rbB->ZeroVelocityOnAxis(push);
                }
                // ▼ 両方動く → 半分ずつ押す
                else if (rbA && rbB) {
                    rbA->AddPosition(push * 0.5f);
                    rbB->AddPosition(-push * 0.5f);
                    rbA->ZeroVelocityOnAxis(push);
                    rbB->ZeroVelocityOnAxis(push);
                }
                // 両方静的なら押し戻しなし
            }

            // ▼ 衝突通知（Enter only）
            a->OnCollisionEnter(b.get());
            b->OnCollisionEnter(a.get());
        }
    }
}