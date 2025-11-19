//==============================================================================
// File        : PlayerPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-19
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "PlayerPrefab.h"

#include "Script/Game/PlayerScript.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Material.h"

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
	obj->GetTransform().position = { 0.0f, 2.5f, 0.0f };
	obj->GetTransform().scale = { 0.5f, 0.75f, 0.5f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/cube.obj");
	modelComp->SetTexture(0, L"Asset/Texture/test.png");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Diffuse = { 0.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Emission = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Shininess = 32.0f;
	modelComp->SetMaterial(mat);
	modelComp->SetLayer(1.0f);

	// --- Rigidbody Ý’è ---
	auto rb = obj->GetComponent<Rigidbody>();
	RigidbodyConfig rbConfig;
	rbConfig.velocity = math::vector3f(0.0f, 0.0f, 0.0f);
	rbConfig.mass = 1.0f;
	rbConfig.useGravity = false;
	rbConfig.gravity = -40.0f;
	rbConfig.drag = 0.5f;
	rb->Configure(rbConfig);
}