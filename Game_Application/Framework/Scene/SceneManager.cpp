//==============================================================================
// File        : SceneManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SceneManager.h"

using namespace Framework;

void SceneManager::LoadScene(std::unique_ptr<Scene> newScene) {
    UnloadScene();
    m_CurrentScene = std::move(newScene);

    if (m_CurrentScene) {

        if (!m_CurrentScene->SceneInitialize()) {
            m_CurrentScene.reset();
            return;
        }

        m_CurrentScene->Awake();
        m_CurrentScene->OnEnable();
        m_CurrentScene->Start();
    }
}

Scene* SceneManager::GetCurrentScene() {
    return m_CurrentScene.get();
}

void SceneManager::Update() {
    if (m_CurrentScene) {
        m_CurrentScene->SceneUpdate();
		m_CurrentScene->Update();
		m_CurrentScene->FixedUpdate();
		m_CurrentScene->LateUpdate();
    }
}
void SceneManager::Draw() {
    if (m_CurrentScene) {
		m_CurrentScene->DrawGizmos();
        m_CurrentScene->Draw();
    }
}
void SceneManager::UnloadScene() {
    if (m_CurrentScene) {
        m_CurrentScene->OnDisable();
        m_CurrentScene->OnDestroy();
        m_CurrentScene->FinalizeInternal();
        m_CurrentScene->SceneFinalize();
        m_CurrentScene.reset();
    }
}