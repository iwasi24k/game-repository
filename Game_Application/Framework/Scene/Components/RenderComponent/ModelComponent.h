//==============================================================================
// File        : ModelComponent.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "RenderComponent.h"

namespace Framework {

	class Model;

    class ModelComponent : public RenderComponent {
	private:
        std::weak_ptr<Model> m_Model;
        float m_Layer;
		std::wstring m_ShaderName;

    public:
        void LoadModel(const std::wstring& path);
        void SetLayer(float layer);
        void SetMaterial(math::vector4f ambient, math::vector4f diffuse, math::vector4f specular, math::vector4f emission, float shininess);
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
