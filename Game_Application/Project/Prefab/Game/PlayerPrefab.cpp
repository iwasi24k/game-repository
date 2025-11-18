//==============================================================================
// File        : PlayerPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "PlayerPrefab.h"

#include "Script/Game/PlayerScript.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/Rigidbody.h"

using namespace Framework;

GameObject* PlayerPrefab::Create(GameObjectManager* mgr) {
    auto obj = mgr->CreateObject("Player");
    obj->AddComponent<PlayerScript>();
    obj->AddComponent<ModelComponent>();
	obj->AddComponent<Rigidbody>();
    Configure(obj);
    return obj;
}

void PlayerPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 0.0f, 0.0f };
	obj->GetTransform().scale = { 1.0f, 1.0f, 1.0f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	if (modelComp) {
		modelComp->LoadModel(L"Asset/Model/cube.obj");
		modelComp->SetMaterial(
			{ 0.2f, 0.2f, 0.2f, 1.0f }, // ambient
			{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
			{ 0.5f, 0.5f, 0.5f, 1.0f }, // specular
			{ 0.0f, 0.0f, 0.0f, 1.0f }, // emission
			32.0f                       // shininess
		);
		modelComp->SetLayer(1.0f);
		modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
		modelComp->SetTexture(0, L"Asset/Texture/test.png");

		// --- Rigidbody Ý’è ---
		RigidbodyConfig rbConfig;
		rbConfig.velocity = math::vector3f(0.0f, 0.0f, 0.0f);
		rbConfig.mass = 1.0f;
		rbConfig.useGravity = false;
		rbConfig.gravity = -40.0f;
		rbConfig.drag = 0.5f;

		auto rb = obj->GetComponent<Rigidbody>();
		if (rb) {
			rb->Configure(rbConfig);
		}
	}
}