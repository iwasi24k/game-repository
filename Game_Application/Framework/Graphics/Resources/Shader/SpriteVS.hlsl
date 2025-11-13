//==============================================================================
// File        : VertexShader.hlsl
// Description : デフォルト頂点シェーダ
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "Common.hlsl"

VSPS_Sprite main(VertexInput_Sprite input)
{
    VSPS_Sprite output;
    matrix WorldViewProjection = mul(mul(World, View), Projection);
    
    // Position をワールドビュー投影に変換
    output.Position = mul(float4(input.Position.xy, 0.0f, 1.0f), WorldViewProjection);

    // テクスチャ座標をそのまま渡す
    output.TexCoord = input.TexCoord;

    return output;
}