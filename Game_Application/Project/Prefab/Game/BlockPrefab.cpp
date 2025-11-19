//==============================================================================
// File        : BlockPrefab.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "BlockPrefab.h"

#include "GameObject.h"
#include "Components/RenderComponent/ModelComponent.h"

using namespace Framework;

GameObject* BlockPrefab::Create(GameObjectManager* mgr) {
	auto obj = mgr->CreateObject("Block");
	obj->AddComponent<ModelComponent>();

	Configure(obj);
	return obj;
}

void BlockPrefab::Configure(GameObject* obj) {

	// --- Transform Ý’è ---
	obj->GetTransform().position = { 0.0f, 0.0f, 0.0f };
	obj->GetTransform().scale = { 0.5f, 0.5f, 0.5f };
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
	}
}