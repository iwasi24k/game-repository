//==============================================================================
// File        : Material.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-10
// Last Update : 2025-11-10
//------------------------------------------------------------------------------
// Overview :
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
        math::vector4f Diffuse{ 1,1,1,1 };
        math::vector4f Ambient{ 0.1f,0.1f,0.1f,1 };
        math::vector4f Specular{ 0.0f,0.0f,0.0f,1 };
        float Shininess = 1.0f;

        std::shared_ptr<Texture> TexturePtr; // テクスチャ参照（null可）
    };
}

#endif // MATERIAL_H