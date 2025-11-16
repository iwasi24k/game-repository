#pragma once

#include "Prefab.h"
#include "GameObjectManager.h"
#include "Components/RenderComponent/SpriteComponent.h"

class TestPrefab : public Framework::Prefab {
public:
	Framework::GameObject* Create(Framework::GameObjectManager* mgr) override {
		auto obj = mgr->CreateObject("Test");
		obj->AddComponent<Framework::SpriteComponent>();
		Inspector(obj);
		return obj;
	}
	void Inspector(Framework::GameObject* obj) override {
		obj->GetTransform().position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f };
		obj->GetTransform().scale = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f };
		obj->GetTransform().rotation = { 1.0f, 1.0f, 0.0f };

		auto spriteComp = obj->GetComponent<Framework::SpriteComponent>();
		if (spriteComp) {
			spriteComp->LoadSprite(L"Asset\\Texture\\nazuna.png");
			spriteComp->SetLayer(0.0f);
			spriteComp->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			spriteComp->LoadShader(L"SpriteShader", L"cso-file\\SpriteVS.cso", L"cso-file\\SpritePS.cso");
		}
	}
};