//==============================================================================
// File        : Scene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
//==============================================================================
#ifndef SCENE_H
#define SCENE_H

#include "GameObjectManager.h"

namespace Framework {

	class Scene {
	private:
		std::unique_ptr<GameObjectManager> m_GameObjectManager;

	public:
		Scene();
		virtual ~Scene();

		virtual bool SceneInitialize() = 0;
		virtual void SceneFinalize() = 0;
		virtual void SceneUpdate() = 0;

		GameObjectManager* GetGameObjectManager() const;

	private:
		void Awake();
		void OnEnable();
		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void DrawGizmos();
		void Draw();
		void OnDisable();
		void OnDestroy();
		void FinalizeInternal();

		friend class SceneManager;
	};
}

#endif // SCENE_H