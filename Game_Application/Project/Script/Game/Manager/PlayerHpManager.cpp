//==============================================================================
// File        : PlayerHpManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "PlayerHpManager.h"
#include "Global/GlobalGameData.h"
#include "Components/RenderComponent/SpriteComponent.h"
#include "Prefab/Game/PlayerHpPrefab.h"
#include "Script/Game/CombatProcessing.h"
#include "Prefab/Game/HitPointPrefab.h"

using namespace Framework;

void PlayerHpManager::Create() {

	m_Player = GetGameObjectManager()->FindObject("Player");
	m_CombatProcessing = m_Player->GetComponent<CombatProcessing>();

	HitPointPrefab hitPointPrefab;
	hitPointPrefab.Create(GetGameObjectManager());

	PlayerHpPrefab playerHpPrefab;
	for (int i = 0; i < m_CombatProcessing->GetHitPoint(); ++i) {
		auto playerHpObj = playerHpPrefab.Create(GetGameObjectManager());
		playerHpObj->GetTransform().position.x += i * (playerHpObj->GetTransform().scale.x) * 2.0f;
		m_HitPoints.push_back(playerHpObj);
	}
}

void PlayerHpManager::Update() {
	
	int currentHp = m_CombatProcessing->GetHitPoint();
	if (currentHp == m_OldHp) return;
	m_OldHp = currentHp;

	for (int i = 0; i < m_HitPoints.size(); ++i) {
		auto spriteComp = m_HitPoints[i]->GetComponent<SpriteComponent>();
		if (spriteComp) {
			if (i < currentHp) {
				spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			}
			else {
				spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			}
		}
	}
}