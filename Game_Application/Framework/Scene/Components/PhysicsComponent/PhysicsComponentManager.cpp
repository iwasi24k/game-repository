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
#include "Framework/Core/Timer.h"

using namespace Framework;

void PhysicsComponentManager::Start(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    for (auto& obj : gameObjects) {
        auto* col = obj->GetComponent<ColliderComponent>();
        if (!col) continue;
        col->SetFromTransform(obj->GetTransform().position);
        m_Colliders.push_back(col);
    }
    auto c = m_Colliders.size();
}

void PhysicsComponentManager::FixedUpdate(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    // Rigidbody の速度で位置を更新
    for (auto* col : m_Colliders) {
        Rigidbody* rb = col->GetOwner()->GetComponent<Rigidbody>();
        if (!rb) continue;
        math::vector3f nextPos = rb->GetOwner()->GetTransform().position + rb->GetVelocity() * Timer::GetInstance().GetDeltaTime();
        rb->GetOwner()->GetTransform().position = nextPos;
    }

    // Collider を最新位置に更新
    for (auto* col : m_Colliders) {
        col->SetFromTransform(col->GetOwner()->GetTransform().position);
    }
    CheckCollisions();
    ResolveCollisions();
}

void PhysicsComponentManager::OnDestroy() {
    m_Colliders.clear();
}

void PhysicsComponentManager::ResolveCollisions() {
    for (auto* col : m_Colliders) {
        if (!col || !col->IsEnabled() || col->IsTrigger()) continue;

        Rigidbody* rb = col->GetOwner()->GetComponent<Rigidbody>();
        if (!rb) continue;

        math::vector3f currentPos = rb->GetOwner()->GetTransform().position;
        float dt = Timer::GetInstance().GetDeltaTime();
        math::vector3f nextPos = currentPos + rb->GetVelocity() * dt;

        col->SetFromTransform(nextPos);

        for (auto* other : m_Colliders) {
            if (other == col || !other->IsEnabled()) continue;

            if (!col->Intersect(*other)) continue;
            
            math::vector3f normal = col->GetCollisionNormal(*other);
            float depth = math::dot(col->GetPenetration(*other), normal);

            if (depth > 0.0f) {
                nextPos += normal * depth;

                float vn = math::dot(rb->GetVelocity(), normal);
                if (vn < 0.0f) {
                    rb->SetVelocity(rb->GetVelocity() - normal * vn);//ここにこない
                }
                col->SetFromTransform(nextPos);
            }       
        }

        rb->GetOwner()->GetTransform().position = nextPos;
    }
}

void PhysicsComponentManager::CheckCollisions() {
    for (size_t i = 0; i < m_Colliders.size(); ++i) {
        ColliderComponent* col = m_Colliders[i];
        if (!col || !col->IsEnabled()) continue;

        for (size_t j = i + 1; j < m_Colliders.size(); ++j) {
            ColliderComponent* other = m_Colliders[j];
            if (!other || !other->IsEnabled()) continue;

            bool isTrigger = col->IsTrigger() || other->IsTrigger();
            bool intersect = col->Intersect(*other);

            if (intersect) {
                if (isTrigger) {
                    auto& prevA = m_TriggerPairs[col];
                    auto& prevB = m_TriggerPairs[other];

                    if (prevA.find(other) == prevA.end()) {
                        col->GetOwner()->OnTriggerEnter(other->GetOwner());
                        other->GetOwner()->OnTriggerEnter(col->GetOwner());

                        prevA.insert(other);
                        prevB.insert(col);
                    }
                    else {
                        col->GetOwner()->OnTriggerStay(other->GetOwner());
                        other->GetOwner()->OnTriggerStay(col->GetOwner());
                    }
                }
                else {
                    auto& prevA = m_CollisionPairs[col];
                    auto& prevB = m_CollisionPairs[other];

                    if (prevA.find(other) == prevA.end()) {
                        col->GetOwner()->OnCollisionEnter(other->GetOwner());
                        other->GetOwner()->OnCollisionEnter(col->GetOwner());

                        prevA.insert(other);
                        prevB.insert(col);
                    }
                    else {
                        col->GetOwner()->OnCollisionStay(other->GetOwner());
                        other->GetOwner()->OnCollisionStay(col->GetOwner());
                    }
                }
            }
            else {
                if (isTrigger) {
                    auto& prevA = m_TriggerPairs[col];
                    auto& prevB = m_TriggerPairs[other];

                    if (prevA.erase(other)) {
                        prevB.erase(col);

                        col->GetOwner()->OnTriggerExit(other->GetOwner());
                        other->GetOwner()->OnTriggerExit(col->GetOwner());
                    }
                }
                else {
                    auto& prevA = m_CollisionPairs[col];
                    auto& prevB = m_CollisionPairs[other];

                    if (prevA.erase(other)) {
                        prevB.erase(col);

                        col->GetOwner()->OnCollisionExit(other->GetOwner());
                        other->GetOwner()->OnCollisionExit(col->GetOwner());
                    }
                }
            }
        }
    }
}
