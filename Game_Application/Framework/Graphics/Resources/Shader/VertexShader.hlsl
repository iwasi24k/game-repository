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

VSPS_Default main(VertexInput_Default input)
{
    VSPS_Default output;

    // ワールド変換
    float4 worldPos = mul(float4(input.Position, 1.0f), World);
    output.WorldPosition = worldPos;

    // ビュー・射影変換
    output.Position = mul(worldPos, View);
    output.Position = mul(output.Position, Projection);

    // 法線（ワールド空間へ）
    output.Normal = mul(float4(input.Normal, 0.0f), World).xyz;
    output.Normal = normalize(output.Normal);

    // 色・UV
    output.Color = input.Color;
    output.TexCoord = input.TexCoord;

    return output;
}