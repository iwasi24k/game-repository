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

VSOutput main(VertexInput_Default input)
{
    VSOutput output;

    float4 worldPos = mul(float4(input.Position, 1.0f), World);
    output.PosH = mul(worldPos, View);
    output.PosH = mul(output.PosH, Projection);

    output.Normal = normalize(mul(float4(input.Normal, 0.0f), World).xyz);
    output.Tex = input.TexCoord;
    output.Color = input.Color;

    return output;
}
