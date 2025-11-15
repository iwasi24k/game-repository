//==============================================================================
// File        : Material.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-12
// Last Update : 2025-11-12
//------------------------------------------------------------------------------
// Overview : Modelのマテリアル情報を格納する構造体
//==============================================================================
#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <wrl/client.h>
#include <d3d11.h>
#include "MathTransform.h"

namespace Framework {

    class Texture; // 既存の Texture クラス

    struct Material {
        math::vector4f Ambient = { 1,1,1,1 };
        math::vector4f Diffuse = { 1,1,1,1 };
        math::vector4f Specular = { 0,0,0,1 };
        math::vector4f Emission = { 0,0,0,1 };
        float Shininess = 0.0f;
		UINT TextureSlot = 0;
        std::shared_ptr<Texture> Texture = nullptr;

        // デフォルトコンストラクタで初期化済み
        Material() = default;
    };
}

#endif // MATERIAL_H