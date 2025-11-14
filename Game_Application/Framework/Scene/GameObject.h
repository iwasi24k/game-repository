//==============================================================================
// File        : GameObject.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
//==============================================================================
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "MathTransform.h"
#include "Component.h"

namespace Framework {

    class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> m_Components;

		bool m_Active = true;
		bool m_Started = false;

        std::string m_Tag = "GameObject";
		math::transform<math::vector3f> m_Transform;

    public:
		// --- Constructor / Destructor ---
        explicit GameObject(const std::string& tag);
        ~GameObject();

		// --- Component Management ---
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args);

        template<typename T>
        T* GetComponent();

		// --- Properties ---
        void SetActive(bool active);
        bool IsActive() const;
        const std::string& GetTag() const;
		const math::transform<math::vector3f>& GetTransform() const;
		math::transform<math::vector3f>& GetTransform();

    private:
        // --- Lifecycle ---
        void Awake();
        void OnEnable();
        void Start();
        void Update();
        void FixedUpdate();
        void LateUpdate();
        void OnDisable();
        void OnDestroy();

		friend class GameObjectManager;
    };

    template<typename T, typename ...Args>
    inline T* GameObject::AddComponent(Args && ...args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->SetOwner(this);
        T* ptr = comp.get();
        m_Components.push_back(std::move(comp));
        return ptr;
    }
    template<typename T>
    inline T* GameObject::GetComponent() {
        for (auto& c : m_Components) {
            if (auto casted = dynamic_cast<T*>(c.get()))
                return casted;
        }
        return nullptr;
    }
} // namespace Framework

#endif // GAME_OBJECT_H