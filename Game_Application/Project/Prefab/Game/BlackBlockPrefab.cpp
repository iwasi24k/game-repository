//==============================================================================
// File        : BlackBlockPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-19
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "BlackBlockPrefab.h"

#include "GameObject.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Components/PhysicsComponent/BoxCollider.h"
#include "Script/Game/BlockScript.h"
#include "Material.h"

using namespace Framework;

GameObject* BlackBlockPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("Block");
	obj->AddComponent<ModelComponent>();
	obj->AddComponent<BoxCollider>();
	obj->AddComponent<BlockScript>();

	Configure(obj);
	return obj;
}

void BlackBlockPrefab::Configure(GameObject* obj) {

	// --- Transform 設定 ---
	obj->GetTransform().position = { 0.0f, 0.0f, 0.0f };
	obj->GetTransform().scale = { 3.0f, 3.0f, 3.0f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent 設定 ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/block.fbx");
	//modelComp->SetTexture(0, L"Asset/Texture/test.png");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mat.Diffuse = { 0.35f, 0.35f, 0.35f, 1.0f };
	mat.Specular = { 0.3f, 0.3f, 0.3f, 1.0f };
	mat.Emission = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Shininess = 32.0f;
	modelComp->SetMaterial(mat);
	modelComp->SetLayer(1.0f);
	modelComp->SetLight(
		{ 0.5f, 1.0f, 0.8f, 0.0f },   // 平行光方向
		{ 1.5f, 1.5f, 1.5f, 1.0f },      // 拡散光強め
		{ 0.5f, 0.5f, 0.5f, 1.0f },      // 環境光少し強め
		{ 0,0,0,1 },                     // ポイント光位置（今回は使わない）
		{ 1,0,0,0 }                      // パラメータ未使用
	);

	auto blockScript = obj->GetComponent<BlockScript>();
	blockScript->SetMaterial(mat);

	// --- BoxCollider 設定 ---
	auto bc = obj->GetComponent<BoxCollider>();
	BoxColliderConfig bcConfig;
	bcConfig.isTrigger = true;
	bc->Configure(bcConfig);
}