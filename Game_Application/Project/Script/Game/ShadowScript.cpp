//==============================================================================
// File        : ShadowScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ShadowScript.h"
#include "GameObject.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/CameraComponent/TopDownCamera.h"
#include "Framework/Core/Timer.h"
#include "Renderer.h"
#include "ManagerHub.h"
#include "Manager/BlockManager.h"

using namespace Framework;

void ShadowScript::Start() {
    // Initialization code here

}

void ShadowScript::Update() {
    // Update code here
    float blockY = GetManagerHub()->FindManager<BlockManager>()->GetBlockHeightAt(GetOwner()->GetTransform());

    Shader::ShadowBuffer sb{};
    sb.ShadowPosition = GetOwner()->GetTransform().position;
    sb.ShadowSize = { 0.8f, 0.8f };
    sb.ShadowStrength = 0.5f;
    sb.FieldPosition = { 0.0f, blockY, 0.0f };
    Renderer::GetInstance().SetBuffer<Shader::ShadowBuffer>(4, sb, Shader::ShaderStage::Pixel);
}
