#include "pch.h"
#include "GameObject.h"

using namespace Framework;

GameObject::GameObject(const std::string& tag) : m_Tag(tag) {}
GameObject::~GameObject() {}

// --- Properties ---
void GameObject::SetActive(bool active) { m_Active = active; }
bool GameObject::IsActive() const { return m_Active; }
const std::string& GameObject::GetTag() const { return m_Tag; }
const math::transform<math::vector3f>& GameObject::GetTransform() const { return m_Transform; }
math::transform<math::vector3f>& GameObject::GetTransform() { return m_Transform; }

// --- Lifecycle ---
void GameObject::Awake() {
	for(auto& comp : m_Components) comp->Awake();
}
void GameObject::OnEnable() {
	for(auto& comp : m_Components) comp->OnEnable();
}
void GameObject::Start() {
	if (!m_Started) {
		m_Started = true;
		for (auto& comp : m_Components) comp->Start();
	}
}
void GameObject::Update() {
	if (!m_Active) return;
	for(auto& comp : m_Components) comp->Update();
}
void GameObject::FixedUpdate() {
	if (!m_Active) return;
	for(auto& comp : m_Components) comp->FixedUpdate();
}
void GameObject::LateUpdate() {
	if (!m_Active) return;
	for(auto& comp : m_Components) comp->LateUpdate();
}
void GameObject::OnDisable() {
	for(auto& comp : m_Components) comp->OnDisable();
}
void GameObject::OnDestroy() {
	for(auto& comp : m_Components) comp->OnDestroy();
	m_Components.clear();
	m_Started = false;
}