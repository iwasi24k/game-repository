//==============================================================================
// File        : Prefab.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-14
// Last Update : 2025-11-14
//------------------------------------------------------------------------------
// Overview :
// 
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
	//	 PlayerPrefab() = default;
	//   ~PlayerPrefab() = default;
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