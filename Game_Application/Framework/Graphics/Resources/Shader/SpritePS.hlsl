//==============================================================================
// File        : PixelShader.hlsl
// Description : デフォルトピクセルシェーダ
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "Common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

float4 main(VSPS_Sprite input) : SV_TARGET
{
    float4 finalColor = g_Texture.Sample(g_Sampler, input.TexCoord) * Color;
    return finalColor;
}
