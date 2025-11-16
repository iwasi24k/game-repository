//==============================================================================
// File        : Prefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// Prefab は、GameObject の生成手順をカプセル化するための基底クラスです。
// Create() により必要なコンポーネント構成や初期設定を一括で構築し、
// Inspector() を通して外部からのプロパティ編集にも対応できます。
// これにより、統一された生成処理・再利用性・拡張性の高いオブジェクト構築を実現します。
//==============================================================================
#ifndef PREFAB_H
#define PREFAB_H

#include "GameObject.h"

namespace Framework {

	class Prefab {
	public:
		Prefab() = default;
		virtual ~Prefab() = default;
		virtual GameObject* Create(GameObjectManager* mgr) = 0;
		virtual void Inspector(GameObject* obj) {}
	};

	// -----------------------------------------------
	// --- Example Prefab ---
	// class PlayerPrefab : public Prefab {
	// public:
	// 	 GameObject* Create(GameObjectManager* mgr) override {
	// 	 	auto obj = mgr->CreateObject("Player");
	// 	 	obj->AddComponent<PlayerMove>();
	// 	 	obj->AddComponent<PlayerAttack>();
	//      Inspector(obj);
	// 	 	return obj;
	// 	 }
	//   void Inspector(GameObject* obj) override {
	//      obj->GetComponent<PlayerMove>()->SetSpeed(5.0f);
	//      obj->GetComponent<PlayerAttack>()->SetDamage(10);
	//   }
	// };
	// -----------------------------------------------
	// --- Example Scene Initialize() ---
	// PlayerPrefab playerPrefab;
	// Pattern1:playerPrefab.Create(GetGameObjectManager());
	// Pattern2:GameObject* obj = playerPrefab.Create(GetGameObjectManager());
	//			obj->GetComponent<PlayerMove>()->SetSpeed(5.0f);
	//			obj->GetComponent<PlayerAttack>()->SetDamage(10);
	// -----------------------------------------------
}

#endif // PREFAB_H