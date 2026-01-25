//==============================================================================
// File        : PlayerHpPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "PlayerHpPrefab.h"

#include "Components/RenderComponent/SpriteComponent.h"

using namespace Framework;

GameObject* PlayerHpPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("PlayerHp");
	obj->AddComponent<SpriteComponent>();

	Configure(obj);
	return obj;
}

void PlayerHpPrefab::Configure(GameObject* obj) {
	obj->GetTransform().position = { SCREEN_CENTER_W * 0.85f, SCREEN_CENTER_H * 1.75f, 1.0f };
	obj->GetTransform().scale = { SCREEN_WIDTH * 0.025f, SCREEN_WIDTH * 0.025f, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

	auto spriteComp = obj->GetComponent<SpriteComponent>();
	if (spriteComp) {
		spriteComp->LoadSprite(L"Asset\\Texture\\HitPoint.png", SpriteDrawMode::Instance);
		spriteComp->SetLayer(1.0f);
		spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
	}
}