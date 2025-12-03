//==============================================================================
// File        : ObjectManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-03
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

namespace Framework {

	class GameObjectManager;

	class ObjectManager {
	public:
		ObjectManager() = default;
		virtual ~ObjectManager() = default;

		virtual void Create() {}
		virtual void Start() {}
		virtual void Update() {}

		GameObjectManager* GetGameObjectManager();
	};
}

#endif // OBJECT_MANAGER_H