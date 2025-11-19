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
#include "GameObject.h"

#include "ModelManager.h"
#include "ShaderManager.h"

using namespace Framework;

void ModelComponent::LoadModel(const std::wstring& path) {
    m_Model = ModelManager::GetInstance().LoadModel(path);

	if (auto model = m_Model.lock()) {
        auto& meshes = model->GetMeshes();
		m_OverrideMaterials.resize(model->GetMeshes().size());
        for (size_t i = 0; i < meshes.size(); ++i) {
            m_OverrideMaterials[i] = meshes[i].MaterialData;
        }
	}
}

void ModelComponent::SetMaterial(const Material& mat) {
	for (auto& m : m_OverrideMaterials) {
        if (!m) m = Material{};
        m->Ambient = mat.Ambient;
        m->Diffuse = mat.Diffuse;
        m->Specular = mat.Specular;
        m->Emission = mat.Emission;
        m->Shininess = mat.Shininess;
	}
}

void ModelComponent::SetTexture(UINT slot, const std::wstring& texturePath) {
	auto texture = TextureManager::GetInstance().LoadTexture(texturePath);

	for (auto& m : m_OverrideMaterials) {
		if (!m) m = Material{};
		m->Texture = texture;
		m->TextureSlot = slot;
	}
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
    math::transform<math::vector3f> transform(position, scale, rotation);
    m_WorldMatrix = transform.toMatrix();
}

void ModelComponent::Draw(const math::matrix& view, const math::matrix& proj) {
    ShaderManager::GetInstance().SetShader(m_ShaderName);
    if (auto model = m_Model.lock()) {

        auto context = Renderer::GetInstance().GetContext();
        auto& meshes = model->GetMeshes();

        math::matrix world = m_WorldMatrix;
        Renderer::GetInstance().SetMatrix(
            world.Transposed(),
            view.Transposed(),
            proj.Transposed()
        );

        for (size_t i = 0; i < meshes.size(); ++i) {

            const Material& mat =
                m_OverrideMaterials[i].has_value()
                ? m_OverrideMaterials[i].value()
                : meshes[i].MaterialData;

            Renderer::GetInstance().SetMaterial(
                mat.Ambient,
                mat.Diffuse,
                mat.Specular,
                mat.Emission,
                mat.Shininess,
                mat.Texture != nullptr
            );

            if (mat.Texture) {
                ShaderManager::GetInstance().SetTexture(
                    mat.TextureSlot, mat.Texture->GetSRV()
                );
            }

			if (mat.Diffuse.w < 1.0f)
				Renderer::GetInstance().SetBlendEnable(true);
			else
				Renderer::GetInstance().SetBlendEnable(false);

            // 頂点バッファなどをセットする
            meshes[i].Draw(context);

            // ★ ここに実際の描画呼び出し
			context->DrawIndexed(meshes[i].IndexCount, 0, 0);
        }
    }
}

