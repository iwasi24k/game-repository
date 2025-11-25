//==============================================================================
// File        : WhiteBlockPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-19
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "WhiteBlockPrefab.h"

#include "GameObject.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Material.h"

using namespace Framework;

GameObject* WhiteBlockPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("Block");
	obj->AddComponent<ModelComponent>();

	Configure(obj);
	return obj;
}

void WhiteBlockPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 0.0f, 0.0f };
	obj->GetTransform().scale = { 1.2f, 1.2f, 1.2f };
	obj->GetTransform().rotation = { 0.0f, 0.0f, 0.0f };

	// --- ModelComponent Ý’è ---
	auto modelComp = obj->GetComponent<ModelComponent>();
	modelComp->LoadModel(L"Asset/Model/block.fbx");
	//modelComp->SetTexture(0, L"Asset/Texture/test.png");
	modelComp->LoadShader(L"ModelShader", L"cso-file\\VertexShader.cso", L"cso-file\\PixelShader.cso");
	Material mat;
	mat.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Emission = { 0.2f, 0.2f, 0.2f, 1.0f };
	mat.Shininess = 32.0f;
	modelComp->SetMaterial(mat);
	modelComp->SetLayer(1.0f);
}