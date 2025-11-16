//==============================================================================
// File        : RenderComponentManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef RENDER_COMPONENT_MANAGER_H
#define RENDER_COMPONENT_MANAGER_H

#include <vector>
#include "GameObject.h"

namespace Framework {

    class RenderComponentManager {
    public:
        void Draw(std::vector<std::unique_ptr<GameObject>>& gameObjects);
    };
}

#endif // RENDER_COMPONENT_MANAGER_H