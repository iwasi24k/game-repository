//==============================================================================
// File        : GameObjectManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"

#include "Components/RenderComponent/RenderComponentManager.h"

using namespace Framework;

GameObjectManager::GameObjectManager() {
	//m_PhysicsManager = std::make_unique<PhysicsManager>();
	m_RenderComponentManager = std::make_unique<RenderComponentManager>();
}
GameObjectManager::~GameObjectManager() {}

GameObject* GameObjectManager::CreateObject(const std::string& tag) {
	auto obj = std::make_unique<GameObject>(tag);
	GameObject* ptr = obj.get();
	m_TagMap.emplace(tag, ptr);
	m_PendingAdd.push_back(std::move(obj));
	return ptr;
}
GameObject* GameObjectManager::FindObject(const std::string& tag) {
	auto range = m_TagMap.equal_range(tag);
	for (auto it = range.first; it != range.second; ++it) {
		GameObject* obj = it->second;
		if (!obj)  continue;
		return obj;
	}
	return nullptr;
}
std::vector<GameObject*> GameObjectManager::FindObjects(const std::string& tag) {
	std::vector<GameObject*> results;
	auto range = m_TagMap.equal_range(tag);
	for (auto it = range.first; it != range.second; ++it) {
		GameObject* obj = it->second;
		if (!obj) continue;
		results.push_back(obj);
	}
	return results;
}

bool GameObjectManager::ExistsTag(const std::string& tag) const
{
	auto range = m_TagMap.equal_range(tag);
	for (auto it = range.first; it != range.second; ++it) {
		GameObject* obj = it->second;
		if (!obj) continue;
		if (obj->IsActive()) return true;
	}
	return false;
}

void GameObjectManager::Awake() {
	FlushPending();
	for (auto& obj : m_Objects) obj->Awake();
}
void GameObjectManager::OnEnable() {
	FlushPending();
	for (auto& obj : m_Objects) obj->OnEnable();
}
void GameObjectManager::Start() {
	FlushPending();
	m_RenderComponentManager->Start(m_Objects);
	for (auto& obj : m_Objects) obj->Start();
}
void GameObjectManager::Update() {
	FlushPending();
	for (auto& obj : m_Objects) obj->Update();
}
void GameObjectManager::FixedUpdate() {
	FlushPending();
	//m_PhysicsManager->FixedUpdate();
	for (auto& obj : m_Objects) obj->FixedUpdate();
}
void GameObjectManager::LateUpdate() {
	FlushPending();
	for (auto& obj : m_Objects) obj->LateUpdate();
}
void GameObjectManager::DrawGizmos() {
	//m_RenderComponentManager->DrawGizmos();
}
void GameObjectManager::Draw() {
	m_RenderComponentManager->Draw(m_Objects);
}
void GameObjectManager::OnDisable() {
	for (auto& obj : m_Objects) obj->OnDisable();
}
void GameObjectManager::OnDestroy() {
	for (auto& obj : m_Objects) obj->OnDestroy();
}
void GameObjectManager::FinalizeInternal() {
	m_TagMap.clear();
	m_PendingAdd.clear();
	m_Objects.clear();
	//m_PhysicsManager.reset();
	m_RenderComponentManager.reset();
}

void GameObjectManager::FlushPending() {
	if (m_PendingAdd.empty()) return;
	for (auto& obj : m_PendingAdd) {
		m_Objects.push_back(std::move(obj));
	}
	m_PendingAdd.clear();
}

