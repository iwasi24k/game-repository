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

    struct GridCell {
        std::vector<ColliderComponent*> colliders;
    };
    struct PairHash {
        size_t operator()(const std::pair<ColliderComponent*, ColliderComponent*>& p) const {
            return std::hash<ColliderComponent*>{}(p.first) ^ (std::hash<ColliderComponent*>{}(p.second) << 1);
        }
    };
	class PhysicsComponentManager {
    private:
        std::vector<ColliderComponent*> m_Colliders;
        std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> m_CollisionPairs;
        std::unordered_map<ColliderComponent*, std::unordered_set<ColliderComponent*>> m_TriggerPairs;
        static const std::unordered_set<ColliderComponent*> m_EmptySet;

        std::unordered_map<int64_t, GridCell> m_Grid;
        float m_CellSize = 3.1f; // AABBÇÃëÂÇ´Ç≥Ç…çáÇÌÇπÇƒí≤êÆ

    public:
        void Start(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void FixedUpdate(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void OnDestroy();
    private:
        void ResolveCollisions();
        void CheckCollisions();

        inline int64_t MakeKey(int x, int y, int z) {
            return (int64_t(x) << 42) ^ (int64_t(y) << 21) ^ int64_t(z);
        }

        inline math::vector3<int> GetCellIndex(const ColliderComponent* col, float cell) {
            const auto& p = col->GetAABB().Center();
            return {
                int(floor(p.x / cell)),
                int(floor(p.y / cell)),
                int(floor(p.z / cell))
            };
        }

        void BuildGrid();
    };
}

#endif // PHYSICS_COMPONENT_MANAGER_H