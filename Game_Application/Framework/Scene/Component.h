//==============================================================================
// File        : Component.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
//==============================================================================
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

namespace Framework {

	class GameObject;

	class Component {
	protected:
		GameObject* m_Owner = nullptr;

	public:
		explicit Component(GameObject* owner) : m_Owner(owner) {}
		virtual ~Component() = default;

		GameObject* GetOwner() const { return m_Owner; }
		GameObject* FindObject(const std::string& tag);

		// --- Lifecycle methods ---
		virtual void Awake() {}
		virtual void OnEnable() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}
		virtual void OnDisable() {}
		virtual void OnDestroy() {}
	};
} // namespace Framework

#endif // COMPONENT_H