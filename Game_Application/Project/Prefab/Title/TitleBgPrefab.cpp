//==============================================================================
// File        : TitleBgPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "TitleBgPrefab.h"
#include "Components/RenderComponent/SpriteComponent.h"

using namespace Framework;

GameObject* TitleBgPrefab::Create(Framework::GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("GameStart");
	obj->AddComponent<SpriteComponent>();

	Configure(obj);
	return obj;
}

void TitleBgPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { SCREEN_CENTER_W, SCREEN_CENTER_H, 1.0f };
	obj->GetTransform().scale = { SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

	auto spriteComp = obj->GetComponent<SpriteComponent>();
	if (spriteComp) {
		spriteComp->LoadSprite(L"Asset\\Texture\\Bg.png", Framework::SpriteDrawMode::Instance);
		spriteComp->SetLayer(0.0f);
		spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
	}
}
