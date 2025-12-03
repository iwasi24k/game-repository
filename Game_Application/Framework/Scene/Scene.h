//==============================================================================
// File        : Scene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// Overview :
// Scene クラスはシーン単位のゲームオブジェクト管理を担い、
// 内部で GameObjectManager を所有し、その全ライフサイクル呼び出しを委譲します。
// コンストラクタで GameObjectManager を生成し、デストラクタで確実に解放します。
// Awake / OnEnable / Start / Update / FixedUpdate / LateUpdate / DrawGizmos / Draw など
// すべてのイベントは GameObjectManager によって処理され、
// Scene 自身は「管理のハブ」として機能します。
// FinalizeInternal や OnDisable / OnDestroy などの終了処理も同様に委譲され、
// シーンの状態管理とゲームオブジェクトの一貫した制御を可能にします。
//==============================================================================
#ifndef SCENE_H
#define SCENE_H

#include "GameObjectManager.h"
#include "ManagerHub.h"

namespace Framework {

	class Scene {
	private:
		std::unique_ptr<GameObjectManager> m_GameObjectManager;
		std::unique_ptr<ManagerHub> m_ManagerHub;

	public:
		Scene();
		virtual ~Scene();

		virtual bool SceneInitialize() = 0;
		virtual void SceneFinalize() = 0;
		virtual void SceneUpdate() = 0;

		GameObjectManager* GetGameObjectManager() const;
		ManagerHub* GetManagerHub() const;

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