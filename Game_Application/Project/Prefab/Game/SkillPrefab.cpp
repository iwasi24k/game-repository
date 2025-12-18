//==============================================================================
// File        : SkillPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-18
// Last Update : 2025-12-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SkillPrefab.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/PhysicsComponent/BoxCollider.h"
#include "Material.h"

using namespace Framework;

GameObject* SkillPrefab::Create(GameObjectManager* mgr) {
    auto obj = mgr->CreateObject("Skill");
    obj->AddComponent<ModelComponent>();
    obj->AddComponent<Rigidbody>();
    obj->AddComponent<BoxCollider>();

    Configure(obj);
    return obj;
}

void SkillPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 23.5f, 0.0f };
	obj->GetTransform().scale = { 0.25f, 0.25f, 0.25f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/block.fbx");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
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
	rbConfig.drag = 0.05f;
	rb->Configure(rbConfig);

	// --- BoxCollider Ý’è ---
	auto bc = obj->GetComponent<BoxCollider>();
	BoxColliderConfig bcConfig;
	bcConfig.isTrigger = true;
	bc->Configure(bcConfig);
}
