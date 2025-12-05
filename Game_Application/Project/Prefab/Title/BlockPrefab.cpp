//==============================================================================
// File        : TitleBlockManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "BlockPrefab.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Project/Script/Title/BgBlockScript.h"
#include "Material.h"

using namespace Framework;

GameObject* BlockPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("TitleBlock");
	obj->AddComponent<ModelComponent>();
	obj->AddComponent<BgBlockScript>();
	Configure(obj);
	return obj;
}

void BlockPrefab::Configure(GameObject* obj) {
	obj->GetTransform().position = { 0.0f, 50.0f, 0.0f };
	obj->GetTransform().scale = { 1.0f, 1.0f, 1.0f };
	obj->GetTransform().rotation = { 1.0f, 1.0f, 1.0f };

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

}