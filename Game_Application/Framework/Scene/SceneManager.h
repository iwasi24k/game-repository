//==============================================================================
// File        : SceneManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// SceneManager は現在アクティブな Scene のライフサイクル管理を担当します。
// LoadScene() は既存シーンを UnloadScene() により安全に破棄した後、
// 新しいシーンをムーブして登録し、SceneInitialize() → Awake() → OnEnable() → Start() の順で初期化を行います。
// Update() は毎フレーム SceneUpdate(), Update(), FixedUpdate(), LateUpdate() を順に呼び出して
// 各種更新処理（シーン単位の管理・フレーム更新・固定更新・後処理）を実行します。
// Draw() はデバッグ用の DrawGizmos() を先に実行し、その後に通常描画の Draw() を実行します。
// UnloadScene() は OnDisable(), OnDestroy(), FinalizeInternal(), SceneFinalize() を順に呼び出して
// シーンを完全に終了・解放し、メモリや状態の不整合を防ぎます。
// このクラスによりシーン切替とライフサイクル呼び出しが一貫して行われ、安定したランタイム動作が保障されます。
//==============================================================================
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include "Scene.h"

namespace Framework {

	class SceneManager {
	private:
        std::unique_ptr<Scene> m_CurrentScene;

		SceneManager() = default;
		~SceneManager() = default;
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

	public:
        static SceneManager& GetInstance() {
            static SceneManager instance;
            return instance;
        }

        void LoadScene(std::unique_ptr<Scene> newScene);

        Scene* GetCurrentScene();

    private:
        void Update();
        void Draw();
        void UnloadScene();

		friend class Application;
	};
}

#endif // SCENE_MANAGER_H