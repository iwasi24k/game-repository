//==============================================================================
// File        : TimerPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "TimerPrefab.h"

#include "GameObject.h"
#include "Components/RenderComponent/SpriteComponent.h"

using namespace Framework;

GameObject* TimerPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("Timer");
	obj->AddComponent<SpriteComponent>();

	Configure(obj);
	return obj;
}

void TimerPrefab::Configure(GameObject* obj) {
	obj->GetTransform().position = { SCREEN_CENTER_W * 0.15f, SCREEN_CENTER_H * 0.25f, 1.0f };
	obj->GetTransform().scale = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.15f, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

	auto spriteComp = obj->GetComponent<SpriteComponent>();
	if (spriteComp) {
		spriteComp->LoadSprite(L"Asset\\Texture\\NumberTexture.png", SpriteDrawMode::Single);
		spriteComp->SetLayer(1.0f);
		spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
	}
}
