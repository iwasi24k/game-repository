//==============================================================================
// File        : ShaderManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このファイルは、DirectX 11 におけるシェーダー関連の共通データ構造体を定義します。
// 頂点・インスタンス・マトリクス・ライト・マテリアルなど、GPU 定数バッファ転送に
// 必要な要素を全て 16 バイト境界でアラインし、HLSL 構造体と一致するよう設計。
// 各構造体は描画シーン全体の情報を効率的に共有するための基本要素です。
// 頂点フォーマット (Vertex / SkinnedVertex) から、描画パラメータ (LightBuffer 等) まで、
// シェーダー通信を統一的に扱うための基礎モジュールとなっています。
//==============================================================================
#ifndef SHADER_TYPES_H
#define SHADER_TYPES_H

#include <d3d11.h>
#include "MathTransform.h"

namespace Shader {

	enum class ShaderStage { Vertex, Pixel };
	enum class VertexLayoutType { Default, Sprite, Skinned };

	struct alignas(16) Vertex {
		math::vector3f Position;   // 12
		float pad0;                // padding 12->16
		math::vector3f Normal;     // 12
		float pad1;                // padding 12->16
		math::vector4f Diffuse;	   // 16
		math::vector2f TexCoord;   // 8
		float pad2[2];             // padding 8->16
	};

	struct alignas(16) SpriteVertex {
		math::vector2f Position;   // 8
		math::vector2f TexCoord;   // 8
	};

	struct alignas(16) SkinnedVertex {
		DirectX::XMFLOAT3 Position;     // 頂点座標
		DirectX::XMFLOAT3 Normal;       // 法線
		DirectX::XMFLOAT2 TexCoord;     // テクスチャ座標
		UINT BoneIndices[4];            // ボーン番号（最大4つの影響）
		float BoneWeights[4];           // 各ボーンの重み（合計1.0になるよう正規化）

		SkinnedVertex() = default;

		SkinnedVertex(
			const DirectX::XMFLOAT3& pos,
			const DirectX::XMFLOAT3& normal,
			const DirectX::XMFLOAT2& tex,
			const UINT* indices,
			const float* weights
		)
			: Position(pos), Normal(normal), TexCoord(tex)
		{
			for (int i = 0; i < 4; ++i) {
				BoneIndices[i] = indices[i];
				BoneWeights[i] = weights[i];
			}
		}
	};

	struct alignas(16) InstanceData {
		math::matrix World; // 64
		float Alpha;        // 4
		float pad[3];       // padding 4->16
	};

	struct alignas(16) MatrixBuffer {
		math::matrix World;      // 64
		math::matrix View;       // 64
		math::matrix Projection; // 64
	};

	struct alignas(16) LightBuffer {
		math::vector4f Direction;   // 16
		math::vector4f Diffuse;     // 16
		math::vector4f Ambient;     // 16
		math::vector4f Position;    // 16
		math::vector4f PointLightParam; // 16
	};

	struct alignas(16) MaterialBuffer {
		math::vector4f Ambient;
		math::vector4f Diffuse;
		math::vector4f Specular;
		math::vector4f Emission;
		float Shininess;
		int TextureEnable;
		float pad;           // 16バイト境界に調整
	};

	struct alignas(16) ColorBuffer {
		math::vector4f Color;
	};

	// サイズチェック（デバッグ用）
	static_assert(sizeof(Vertex) % 16 == 0, "Vertex must be 16-byte aligned");
	static_assert(sizeof(InstanceData) % 16 == 0, "InstanceData must be 16-byte aligned");
	static_assert(sizeof(MatrixBuffer) % 16 == 0, "MatrixBuffer must be 16-byte aligned");
	static_assert(sizeof(LightBuffer) % 16 == 0, "LightBuffer must be 16-byte aligned");
	static_assert(sizeof(MaterialBuffer) % 16 == 0, "MaterialBuffer must be 16-byte aligned");
	static_assert(sizeof(ColorBuffer) % 16 == 0, "ColorBuffer must be 16-byte aligned");
}


#endif // SHADER_TYPES_H