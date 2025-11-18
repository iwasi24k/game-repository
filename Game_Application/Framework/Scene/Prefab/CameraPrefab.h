//==============================================================================
// File        : CameraPrefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef CAMERA_PREFAB_H
#define CAMERA_PREFAB_H

#include "Prefab.h"

namespace Framework {

	class CameraPrefab : public Prefab {
	public:
		GameObject* Create(GameObjectManager* mgr) override;
		void Configure(GameObject* obj) override;
	};
}

#endif // CAMERA_PREFAB_H