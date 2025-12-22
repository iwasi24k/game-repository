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
#include "Script/Game/JumpScript.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/PhysicsComponent/BoxCollider.h"
#include "Material.h"
#include "Script/Game/ShadowScript.h"
#include "Script/Game/CombatProcessing.h"

using namespace Framework;

GameObject* PlayerPrefab::Create(GameObjectManager* mgr) {
    auto obj = mgr->CreateObject("Player");
    obj->AddComponent<PlayerScript>();
    obj->AddComponent<JumpScript>();
    obj->AddComponent<ModelComponent>();
	obj->AddComponent<Rigidbody>();
	obj->AddComponent<BoxCollider>();
	obj->AddComponent<ShadowScript>();
	obj->AddComponent<CombatProcessing>();

    Configure(obj);
    return obj;
}

void PlayerPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 3.5f, 0.0f };
	obj->GetTransform().scale = { 1.0f, 1.0f, 1.0f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/block.fbx");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 0.1f, 1.0f };
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
	rbConfig.useGravity = true;
	rbConfig.gravity = -9.8f;
	rbConfig.drag = 0.05f;
	rb->Configure(rbConfig);

	auto cp = obj->GetComponent<CombatProcessing>();
	cp->SetHitPoint(5);
	cp->SetAttackCooldown(2.0f);
}