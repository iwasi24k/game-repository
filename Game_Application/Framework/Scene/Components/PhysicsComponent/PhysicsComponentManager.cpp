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
#include <array>

using namespace Framework;

const std::unordered_set<ColliderComponent*> PhysicsComponentManager::m_EmptySet{};

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
            if (other == col || !other->IsEnabled() || other->IsTrigger()) continue;

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
    BuildGrid();

    static constexpr std::array neigh = [] {
        std::array<std::array<int, 3>, 27> tmp{};
        int k = 0;
        for (int z = -1; z <= 1; ++z)
            for (int y = -1; y <= 1; ++y)
                for (int x = -1; x <= 1; ++x)
                    tmp[k++] = { x,y,z };
        return tmp;
        }();

    std::unordered_set<std::pair<ColliderComponent*, ColliderComponent*>, PairHash> processedPairs;

    for (auto& [key, cell] : m_Grid) {
        for (auto* col : cell.colliders) {
            if (!col || !col->IsEnabled()) continue;

            const auto base = GetCellIndex(col, m_CellSize);

            for (const auto& d : neigh) {
                const math::vector3<int> chk{ base.x + d[0], base.y + d[1], base.z + d[2] };
                const int64_t key2 = MakeKey(chk.x, chk.y, chk.z);

                if (auto it = m_Grid.find(key2); it != m_Grid.end()) {
                    for (auto* other : it->second.colliders) {
                        if (!other || !other->IsEnabled() || other <= col) continue;

                        auto pairKey = std::make_pair(col, other);
                        if (processedPairs.contains(pairKey)) continue;
                        processedPairs.insert(pairKey);

                        bool isTrigger = col->IsTrigger() || other->IsTrigger();
                        bool intersects = col->GetAABB().FastIntersect(other->GetAABB()) && col->Intersect(*other);

                        auto& colSet = isTrigger ? m_TriggerPairs[col] : m_CollisionPairs[col];
                        auto& otherSet = isTrigger ? m_TriggerPairs[other] : m_CollisionPairs[other];

                        if (intersects) {
                            if (!colSet.contains(other)) {
                                if (isTrigger) {
                                    col->GetOwner()->OnTriggerEnter(other->GetOwner());
                                    other->GetOwner()->OnTriggerEnter(col->GetOwner());
                                }
                                else {
                                    col->GetOwner()->OnCollisionEnter(other->GetOwner());
                                    other->GetOwner()->OnCollisionEnter(col->GetOwner());
                                }
                                colSet.insert(other);
                                otherSet.insert(col);
                            }
                            else {
                                if (isTrigger) {
                                    col->GetOwner()->OnTriggerStay(other->GetOwner());
                                    other->GetOwner()->OnTriggerStay(col->GetOwner());
                                }
                                else {
                                    col->GetOwner()->OnCollisionStay(other->GetOwner());
                                    other->GetOwner()->OnCollisionStay(col->GetOwner());
                                }
                            }
                        }
                        else {
                            if (colSet.erase(other)) {
                                otherSet.erase(col);
                                if (isTrigger) {
                                    col->GetOwner()->OnTriggerExit(other->GetOwner());
                                    other->GetOwner()->OnTriggerExit(col->GetOwner());
                                }
                                else {
                                    col->GetOwner()->OnCollisionExit(other->GetOwner());
                                    other->GetOwner()->OnCollisionExit(col->GetOwner());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void PhysicsComponentManager::BuildGrid() {
    m_Grid.clear();
    for (auto* col : m_Colliders) {
        if (!col || !col->IsEnabled()) continue;

        const math::vector3<int> cell = GetCellIndex(col, m_CellSize);
        const int64_t key = MakeKey(cell.x, cell.y, cell.z);
        m_Grid[key].colliders.push_back(col);
    }
}

//-------------------------------------------------------------------------------------------------------

//void PhysicsComponentManager::CheckCollisions() {
//    for (size_t i = 0; i < m_Colliders.size(); ++i) {
//        ColliderComponent* col = m_Colliders[i];
//        if (!col || !col->IsEnabled()) continue;
//
//        for (size_t j = i + 1; j < m_Colliders.size(); ++j) {
//            ColliderComponent* other = m_Colliders[j];
//            if (!other || !other->IsEnabled()) continue;
//
//            bool isTrigger = col->IsTrigger() || other->IsTrigger();
//            bool intersect = col->Intersect(*other);
//
//            if (intersect) {
//                if (isTrigger) {
//                    auto& prevA = m_TriggerPairs[col];
//                    auto& prevB = m_TriggerPairs[other];
//
//                    if (prevA.find(other) == prevA.end()) {
//                        col->GetOwner()->OnTriggerEnter(other->GetOwner());
//                        other->GetOwner()->OnTriggerEnter(col->GetOwner());
//
//                        prevA.insert(other);
//                        prevB.insert(col);
//                    }
//                    else {
//                        col->GetOwner()->OnTriggerStay(other->GetOwner());
//                        other->GetOwner()->OnTriggerStay(col->GetOwner());
//                    }
//                }
//                else {
//                    auto& prevA = m_CollisionPairs[col];
//                    auto& prevB = m_CollisionPairs[other];
//
//                    if (prevA.find(other) == prevA.end()) {
//                        col->GetOwner()->OnCollisionEnter(other->GetOwner());
//                        other->GetOwner()->OnCollisionEnter(col->GetOwner());
//
//                        prevA.insert(other);
//                        prevB.insert(col);
//                    }
//                    else {
//                        col->GetOwner()->OnCollisionStay(other->GetOwner());
//                        other->GetOwner()->OnCollisionStay(col->GetOwner());
//                    }
//                }
//            }
//            else {
//                if (isTrigger) {
//                    auto& prevA = m_TriggerPairs[col];
//                    auto& prevB = m_TriggerPairs[other];
//
//                    if (prevA.erase(other)) {
//                        prevB.erase(col);
//
//                        col->GetOwner()->OnTriggerExit(other->GetOwner());
//                        other->GetOwner()->OnTriggerExit(col->GetOwner());
//                    }
//                }
//                else {
//                    auto& prevA = m_CollisionPairs[col];
//                    auto& prevB = m_CollisionPairs[other];
//
//                    if (prevA.erase(other)) {
//                        prevB.erase(col);
//
//                        col->GetOwner()->OnCollisionExit(other->GetOwner());
//                        other->GetOwner()->OnCollisionExit(col->GetOwner());
//                    }
//                }
//            }
//        }
//    }
//}
