//==============================================================================
// File        : SpriteComponent.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// Overview :
// SpriteComponent は、2D スプライトの描画制御を担当するコンポーネントです。
// スプライトリソースの読み込み、色・レイヤー・UV・トランスフォーム設定、
// そして描画に必要なシェーダーの指定など、描画に必要な一連の機能を提供します。
// GameObject から独立して描画管理を行うことで、柔軟で拡張性の高い 2D 表現を実現します。
//==============================================================================
#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "RenderComponent.h"

namespace Framework {

    class Sprite;
    enum class SpriteDrawMode { Single, Instance };

    class SpriteComponent : public RenderComponent {
    private:
        SpriteDrawMode m_SpriteDrawMode = SpriteDrawMode::Single;
        std::shared_ptr<Sprite> m_Sprite;
        std::weak_ptr<Sprite> m_SpriteInstance;

        float m_Layer;
        std::wstring m_ShaderName;
        math::matrix m_WorldMatrix = math::matrix::Identity();
        math::vector4f m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

    public:
        void LoadSprite(const std::wstring& path, SpriteDrawMode mode = SpriteDrawMode::Single);
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
        void OnDestroy() override;

        float GetLayer() const { return m_Layer; }
        const math::vector4f& GetColor() const { return m_Color; }
    };
}

#endif // MODEL_COMPONENT_H
