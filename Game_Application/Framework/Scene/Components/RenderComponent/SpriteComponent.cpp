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
#include "Renderer.h"

using namespace Framework;

void SpriteComponent::LoadSprite(const std::wstring& path, SpriteDrawMode mode) {
	m_SpriteDrawMode = mode;
	if (mode == SpriteDrawMode::Single) {
		m_Sprite = std::make_shared<Sprite>();
		auto tex = TextureManager::GetInstance().LoadTexture(path);
		m_Sprite->SetTexture(tex);
		m_Sprite->Initialize();
	}
	else {
		m_SpriteInstance = SpriteManager::GetInstance().LoadSprite(path);
	}
}

void SpriteComponent::SetLayer(float layer) {
	m_Layer = layer;
}

void SpriteComponent::SetColor(math::vector4f color) {
	m_Color = color;
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
	math::transform<math::vector3f> t;
	t.position = { position.x,position.y,0 };
	t.scale = { scale.x,scale.y,1 };
	t.rotation = { 0,0,rotation.z };
	m_WorldMatrix = t.toMatrix();
}

void SpriteComponent::SetUV(float u0, float v0, float u1, float v1) {
	if (m_SpriteDrawMode == SpriteDrawMode::Single) {
		m_Sprite->SetUV(u0, v0, u1, v1);
	}
	else {
		m_SpriteInstance.lock()->SetUV(u0, v0, u1, v1);
	}
}

void SpriteComponent::Draw() {
	ShaderManager::GetInstance().SetShader(m_ShaderName);

	auto& renderer = Renderer::GetInstance();
	auto& shader = ShaderManager::GetInstance();

	math::matrix view = math::matrix::Identity();
	math::matrix proj = math::matrix::OrthographicOffCenterLH(0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 1);

	renderer.SetMatrix(m_WorldMatrix.Transposed(), view, proj.Transposed());
	renderer.SetColor(m_Color);

	if (m_SpriteDrawMode == SpriteDrawMode::Single) {
		m_Sprite->Draw();
	}
	else {
		m_SpriteInstance.lock()->Draw();
	}
}

void SpriteComponent::OnDestroy() {
	m_Sprite.reset();
}