//==============================================================================
// File        : SpriteComponent.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SpriteComponent.h"
#include "SpriteManager.h"

#include "ShaderManager.h"

using namespace Framework;

void SpriteComponent::LoadSprite(const std::wstring& path) {
	m_Sprite = SpriteManager::GetInstance().LoadSprite(path);
}

void SpriteComponent::SetLayer(float layer) {
	m_Layer = layer;
}

void SpriteComponent::SetColor(math::vector4f color) {
	m_Sprite.lock()->SetColor(color);
}

void SpriteComponent::SetShaderName(const std::wstring& name) {
	m_ShaderName = name;
}

void SpriteComponent::LoadPixelShader(const std::wstring& psPath) {
	ShaderManager::GetInstance().LoadPS(m_ShaderName, psPath);
}

void SpriteComponent::LoadVertexShader(const std::wstring& vsPath) {
	ShaderManager::GetInstance().LoadVS(m_ShaderName, vsPath, Shader::VertexLayoutType::Sprite);
}

void SpriteComponent::LoadShader(const std::wstring& name, const std::wstring& vsPath, const std::wstring& psPath) {
	SetShaderName(name);
	LoadVertexShader(vsPath);
	LoadPixelShader(psPath);
}

void SpriteComponent::SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) {
	m_Sprite.lock()->SetTransform(
		math::vector2f(position.x, position.y),
		math::vector2f(scale.x, scale.y),
		rotation.z
	);
}

void SpriteComponent::SetUV(float u0, float v0, float u1, float v1) {
	m_Sprite.lock()->SetUV(u0, v0, u1, v1);
}

void SpriteComponent::Draw() {
	ShaderManager::GetInstance().SetShader(m_ShaderName);
	m_Sprite.lock()->Draw();
}
