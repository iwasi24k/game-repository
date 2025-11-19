//==============================================================================
// File        : RenderComponentManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include <vector>
#include "GameObject.h"

namespace Framework {

    class BlockManager {
    private:
        GameObjectManager* m_GameObjectManager = nullptr;
		std::vector<GameObject*> m_Blocks;

		const int m_BlockCountX = 15;
		const int m_BlockCountZ = 15;

    public:
        void Create(GameObjectManager* mgr);
        void Update();
    };
}

#endif // BLOCK_MANAGER_H