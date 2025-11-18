//==============================================================================
// File        : Component.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// Component は GameObject に付随する振る舞いを表す基底クラスです。
// 所有者である GameObject への参照を保持し、そこから他のオブジェクト検索も可能。
// Awake / OnEnable / Start / Update / FixedUpdate / LateUpdate / OnDisable / OnDestroy といった
// ライフサイクル関数を仮想メソッドとして備え、必要な機能を派生クラス側で自由に拡張できます。
// これにより、柔軟な振る舞い追加と統一された処理フローを備えたコンポーネント方式を実現します。
//==============================================================================
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

namespace Framework {

	class GameObject;

	class Component {
	protected:
		GameObject* m_Owner = nullptr;

	public:
		explicit Component() = default;
		virtual ~Component() = default;

		void SetOwner(GameObject* owner) { m_Owner = owner; }
		GameObject* GetOwner() const { return m_Owner; }
		GameObject* FindObject(const std::string& tag);
		std::vector<GameObject*> FindObjects(const std::string& tag);

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