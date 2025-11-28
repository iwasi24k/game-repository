//==============================================================================
// File        : PhysicsComponentManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef PHYSICS_COMPONENT_MANAGER_H
#define PHYSICS_COMPONENT_MANAGER_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "GameObject.h"

namespace Framework {

	class PhysicsComponentManager {
    private:
        std::vector<ColliderComponent*> m_Colliders;
        std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> m_CollisionPairs;
        std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> m_TriggerPairs;

    public:
        void Start(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void FixedUpdate(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void OnDestroy();
    private:
        void ResolveCollisions();
        void CheckCollisions();
    };
}

#endif // PHYSICS_COMPONENT_MANAGER_H