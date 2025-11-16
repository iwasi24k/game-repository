//==============================================================================
// File        : Scene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Scene.h"

using namespace Framework;

Scene::Scene() {
	m_GameObjectManager = std::make_unique<GameObjectManager>();
}
Scene::~Scene() {
	m_GameObjectManager.reset();
}

GameObjectManager* Scene::GetGameObjectManager() const {
	return m_GameObjectManager.get(); 
}

void Scene::Awake() {
	m_GameObjectManager->Awake();
}
void Scene::OnEnable() {
	m_GameObjectManager->OnEnable();
}
void Scene::Start() {
	m_GameObjectManager->Start();
}
void Scene::Update() {
	m_GameObjectManager->Update();
}
void Scene::FixedUpdate() {
	m_GameObjectManager->FixedUpdate();
}
void Scene::LateUpdate() {
	m_GameObjectManager->LateUpdate();
}
void Scene::DrawGizmos() {
	m_GameObjectManager->DrawGizmos();
}
void Scene::Draw() {
	m_GameObjectManager->Draw();
}
void Scene::OnDisable() {
	m_GameObjectManager->OnDisable();
}
void Scene::OnDestroy() {
	m_GameObjectManager->OnDestroy();
}
void Scene::FinalizeInternal() {
	m_GameObjectManager->FinalizeInternal();
}

