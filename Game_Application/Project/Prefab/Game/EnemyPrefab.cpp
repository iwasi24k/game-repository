//==============================================================================
// File        : EnemyPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "EnemyPrefab.h"

#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/PhysicsComponent/BoxCollider.h"
#include "Material.h"
#include "Script/Game/EnemyScript.h"
#include "Script/Game/ShadowScript.h"

using namespace Framework;

GameObject* EnemyPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("Enemy");
	obj->AddComponent<ModelComponent>();
	obj->AddComponent<Rigidbody>();
	obj->AddComponent<BoxCollider>();
	obj->AddComponent<EnemyScript>();
	//obj->AddComponent<ShadowScript>();

	Configure(obj);
	return obj;
}

void EnemyPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 5.0f, 0.0f };
	obj->GetTransform().scale = { 1.0f, 1.0f, 1.0f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/block.fbx");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Diffuse = { 0.75f, 0.0f, 0.75f, 1.0f };
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

	auto boxCollider = obj->GetComponent<BoxCollider>();
	BoxColliderConfig bc;
	bc.sizeOffset = { 0.2f, 0.1f , 0.2f};
	boxCollider->Configure(bc);
}