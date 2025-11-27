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
#include "GameObject.h"

namespace Framework {

	class PhysicsComponentManager {
    public:
        void Start(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void Update(std::vector<std::unique_ptr<GameObject>>& gameObjects);

        void CollectObjects(std::vector<std::unique_ptr<GameObject>>& gameObjects);
    };
}

#endif // PHYSICS_COMPONENT_MANAGER_H