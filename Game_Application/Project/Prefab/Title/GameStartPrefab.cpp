//==============================================================================
// File        : GameStartPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "GameStartPrefab.h"
#include "Components/RenderComponent/SpriteComponent.h"
#include "GameObject.h"

using namespace Framework;

GameObject* GameStartPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("GameStart");
	obj->AddComponent<SpriteComponent>();

	Configure(obj);
	return obj;
}

void GameStartPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 1.0f };
	obj->GetTransform().scale = { SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

	auto spriteComp = obj->GetComponent<SpriteComponent>();
	if (spriteComp) {
		spriteComp->LoadSprite(L"Asset\\Texture\\Start.png", Framework::SpriteDrawMode::Instance);
		spriteComp->SetLayer(10.0f);
		spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
	}
}
