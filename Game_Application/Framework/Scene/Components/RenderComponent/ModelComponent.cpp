//==============================================================================
// File        : ModelComponent.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ModelComponent.h"

#include "ModelManager.h"
#include "ShaderManager.h"

using namespace Framework;

void ModelComponent::LoadModel(const std::wstring& path) {
    m_Model = ModelManager::GetInstance().LoadModel(path);
}

void ModelComponent::SetMaterial(math::vector4f ambient, math::vector4f diffuse, math::vector4f specular, math::vector4f emission, float shininess) {
	Material material;
	material.Ambient = ambient;
	material.Diffuse = diffuse;
	material.Specular = specular;
	material.Shininess = shininess;
	material.Emission = emission;
	m_Model.lock()->SetOverrideMaterial(material);
}

void ModelComponent::SetTexture(UINT slot, const std::wstring& texturePath) {
	m_Model.lock()->SetOverrideTexture(slot, texturePath);
}

void ModelComponent::SetLight(math::vector4f direction, math::vector4f diffuse, math::vector4f ambient, math::vector4f position, math::vector4f pointLightParam) {
	Renderer::GetInstance().SetLight(direction, diffuse, ambient, position, pointLightParam);
}

void ModelComponent::SetLayer(float layer) {
	m_Layer = layer;
}

void ModelComponent::SetShaderName(const std::wstring& name) { 
	m_ShaderName = name; 
}

void ModelComponent::LoadPixelShader(const std::wstring& psPath) {
	ShaderManager::GetInstance().LoadPS(m_ShaderName, psPath);
}

void ModelComponent::LoadVertexShader(const std::wstring& vsPath) {
	ShaderManager::GetInstance().LoadVS(m_ShaderName, vsPath);
}

void ModelComponent::LoadShader(const std::wstring& name, const std::wstring& vsPath, const std::wstring& psPath) {
	m_ShaderName = name;
	ShaderManager::GetInstance().LoadVS(name, vsPath);
	ShaderManager::GetInstance().LoadPS(name, psPath);
}

void ModelComponent::SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) {
	m_Model.lock()->SetTransform(position, scale, rotation);
}

void ModelComponent::Draw(const math::matrix& view, const math::matrix& proj) {
	ShaderManager::GetInstance().SetShader(m_ShaderName);
	m_Model.lock()->Draw(view, proj);
}
