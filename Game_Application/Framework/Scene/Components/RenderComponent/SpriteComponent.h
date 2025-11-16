//==============================================================================
// File        : SpriteComponent.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "RenderComponent.h"

namespace Framework {

    class Sprite;

    class SpriteComponent : public RenderComponent {
    private:
        std::weak_ptr<Sprite> m_Sprite;
        float m_Layer;
        std::wstring m_ShaderName;

    public:
        void LoadSprite(const std::wstring& path);
        void SetLayer(float layer);
        void SetColor(math::vector4f color);
        void SetTexture(UINT slot, const std::wstring& texturePath);

        void SetShaderName(const std::wstring& name) override;
        void LoadPixelShader(const std::wstring& psPath) override;
        void LoadVertexShader(const std::wstring& vsPath) override;
        void LoadShader(const std::wstring& name, const std::wstring& vsPath, const std::wstring& psPath) override;
        void SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) override;
		void SetUV(float u0, float v0, float u1, float v1);

        void Draw() override;

        float GetLayer() const { return m_Layer; }
    };
}

#endif // MODEL_COMPONENT_H
