//==============================================================================
// File        : TitleLogoPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "TitleLogoPrefab.h"
#include "GameObject.h"

using namespace Framework;

GameObject* TitleLogoPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("TitleName");
	obj->AddComponent<SpriteComponent>();
	Configure(obj);
	return obj;
}

void TitleLogoPrefab::Configure(GameObject* obj) {
	obj->GetTransform().position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 1.0f };
	obj->GetTransform().scale = { SCREEN_WIDTH / 3 + 100.0f, SCREEN_HEIGHT / 3 - 100.0f, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

	auto spriteComp = obj->GetComponent<SpriteComponent>();
	if (spriteComp) {
		spriteComp->LoadSprite(L"Asset\\Texture\\TitleLogo.png", Framework::SpriteDrawMode::Instance);
		spriteComp->SetLayer(10.0f);
		spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
	}
}