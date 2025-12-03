//==============================================================================
// File        : Scene.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Scene.h"

using namespace Framework;

Scene::Scene() {
	m_ManagerHub = std::make_unique<ManagerHub>();
	m_GameObjectManager = std::make_unique<GameObjectManager>();
}
Scene::~Scene() {
	m_GameObjectManager.reset();
	m_ManagerHub.reset();
}

GameObjectManager* Scene::GetGameObjectManager() const {
	return m_GameObjectManager.get(); 
}

ManagerHub* Scene::GetManagerHub() const {
	return m_ManagerHub.get();
}

void Scene::Awake() {
	m_ManagerHub->CreateAll();
	m_GameObjectManager->Awake();
}
void Scene::OnEnable() {
	m_GameObjectManager->OnEnable();
}
void Scene::Start() {
	m_ManagerHub->StartAll();
	m_GameObjectManager->Start();
}
void Scene::Update() {
	m_ManagerHub->UpdateAll();
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

