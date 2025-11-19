//==============================================================================
// File        : ModelComponent.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// Overview :
// ModelComponent は、3D モデルの描画制御を担当するコンポーネントです。
// モデルリソースの読み込み、マテリアル設定、テクスチャ差し替え、ライト・シェーダー制御、
// そして座標変換と描画処理など、3D 表現に必要な一連の機能を提供します。
// GameObject とは独立して描画設定を保持することで、柔軟かつ拡張性の高い 3D 表現を実現します。
//==============================================================================
#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include <optional>
#include "RenderComponent.h"

namespace Framework {

	class Model;
    class Material;

    class ModelComponent : public RenderComponent {
	private:
        std::weak_ptr<Model> m_Model;
        float m_Layer;
		std::wstring m_ShaderName;
		math::matrix m_WorldMatrix = math::matrix::Identity();
        std::vector<std::optional<Material>> m_OverrideMaterials;

    public:
        void LoadModel(const std::wstring& path);
        void SetLayer(float layer);
        void SetMaterial(const Material& mat);
        void SetTexture(UINT slot, const std::wstring& texturePath);

		void SetLight(math::vector4f direction, math::vector4f diffuse, math::vector4f ambient, math::vector4f position, math::vector4f pointLightParam);

        void SetShaderName(const std::wstring& name) override;
		void LoadPixelShader(const std::wstring& psPath) override;
		void LoadVertexShader(const std::wstring& vsPath) override;
		void LoadShader(const std::wstring& name, const std::wstring& vsPath, const std::wstring& psPath) override;
		void SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) override;
        void Draw(const math::matrix& view, const math::matrix& proj) override;

		float GetLayer() const { return m_Layer; }
    };
}

#endif // MODEL_COMPONENT_H
