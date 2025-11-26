//==============================================================================
// File        : GameObject.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// GameObject はシーン内の個々の実体を表し、タグ、アクティブ状態、Transform、
// そして複数のコンポーネントを内包する基本単位です。
// Awake / OnEnable / Start / Update / FixedUpdate / LateUpdate / OnDisable / OnDestroy により、
// Unity ライクなライフサイクルを自然に表現し、各コンポーネントへ順序通りに処理を伝搬します。
// Active フラグにより Update 系処理の停止を制御し、Start は一度だけ実行されるよう管理。
// 破棄時には全コンポーネントの OnDestroy を呼び、内部リストを安全にクリアします。
// Transform も保持しており、位置・回転・スケールを通じてシーン内の構造制御を担います。
//==============================================================================
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "MathTransform.h"
#include "Component.h"
#include "Components/PhysicsComponent/ColliderComponent.h"

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

        void OnCollisionEnter(GameObject* other) { for (auto& c : m_Components) c->OnCollisionEnter(other); }
        void OnCollisionStay(GameObject* other) { for (auto& c : m_Components) c->OnCollisionStay(other); }
        void OnCollisionExit(GameObject* other) { for (auto& c : m_Components) c->OnCollisionExit(other); }
        void OnTriggerEnter(GameObject* other) { for (auto& c : m_Components) c->OnTriggerEnter(other); }
        void OnTriggerStay(GameObject* other) { for (auto& c : m_Components) c->OnTriggerStay(other); }
        void OnTriggerExit(GameObject* other) { for (auto& c : m_Components) c->OnTriggerExit(other); }

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