//==============================================================================
// File        : Sprite.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef SPRITE_H
#define SPRITE_H

#include <d3d11.h>
#include <wrl/client.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "Framework/Graphics/Texture/Texture.h"
#include "MathTransform.h"

namespace Framework {

    struct UVRect { float u0, v0, u1, v1; };

    class Sprite {
    private:
        std::shared_ptr<Texture> m_Texture;

        float m_Width = 1.0f;
        float m_Height = 1.0f;
        UVRect m_UV{ 0.0f, 0.0f, 1.0f, 1.0f };

		math::matrix m_TransformMatrix;
		math::vector4f m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

        Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;

    public:
        Sprite();
        ~Sprite();

        bool Initialize();
        void Finalize();

        void SetTexture(std::shared_ptr<Texture> texture);
        void SetSize(float width, float height);
        void SetUV(float u0, float v0, float u1, float v1);
        void SetTransform(const math::transform<math::vector2f>& transform);
        void SetTransform(const math::vector2f& position, const math::vector2f& scale = {1.0f, 1.0f}, float rotation = 0.0f);
        void SetColor(const math::vector4f& color);

        void Draw();

    private:
        void CreateVertexBuffer(ID3D11Device* device);
        void UpdateVertexBuffer();
    };
}

#endif // SPRITE_H