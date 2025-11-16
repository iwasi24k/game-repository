#pragma once

#include "Prefab.h"
#include "GameObjectManager.h"
#include "Script/Game/PlayerScript.h"
#include "Components/RenderComponent/ModelComponent.h"

class PlayerPrefab : public Framework::Prefab {
public:
    Framework::GameObject* Create(Framework::GameObjectManager* mgr) override {
        auto obj = mgr->CreateObject("Player");
		obj->AddComponent<PlayerScript>();
		obj->AddComponent<Framework::ModelComponent>();
        Inspector(obj);
        return obj;
    }
    void Inspector(Framework::GameObject* obj) override {
		obj->GetTransform().position = { -7.0f, 0.0f, 0.0f };
		obj->GetTransform().scale = { 1.0f, 1.0f, 1.0f };
		obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };
		auto modelComp = obj->GetComponent<Framework::ModelComponent>();
		if (modelComp) {
			modelComp->LoadModel(L"Asset/Model/cube.obj");
			modelComp->SetMaterial(
				{ 0.2f, 0.2f, 0.2f, 1.0f }, // ambient
				{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
				{ 0.5f, 0.5f, 0.5f, 1.0f }, // specular
				{ 0.0f, 0.0f, 0.0f, 1.0f }, // emission
				32.0f                      // shininess
			);
			modelComp->SetLayer(1.0f);
			modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
			modelComp->SetTexture(0, L"Asset/Texture/test.png");
		}
    }
};