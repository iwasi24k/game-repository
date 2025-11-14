//==============================================================================
// File        : SceneManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
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