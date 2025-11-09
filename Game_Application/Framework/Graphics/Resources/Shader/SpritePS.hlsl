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

Texture2D diffuseTex : register(t0);
SamplerState samp : register(s0);

float4 main(VertexOutput_Sprite input) : SV_TARGET
{
    return diffuseTex.Sample(samp, input.TexCoord);
}
