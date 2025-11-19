#pragma once

#include "Prefab.h"
#include "GameObjectManager.h"
#include "Components/RenderComponent/SpriteComponent.h"

class TestPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override {
		auto obj = mgr->CreateObject("Test");
		obj->AddComponent<Framework::SpriteComponent>();
		Configure(obj);
		return obj;
	}
	void Configure(Framework::GameObject* obj) override {
		obj->GetTransform().position = { 170.0f, 100.0f, 1.0f };
		obj->GetTransform().scale = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 1.0f };
		obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

		auto spriteComp = obj->GetComponent<Framework::SpriteComponent>();
		if (spriteComp) {
			spriteComp->LoadSprite(L"Asset\\Texture\\nazuna.png", Framework::SpriteDrawMode::Instance);
			spriteComp->SetLayer(10.0f);
			spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
		}
	}
};