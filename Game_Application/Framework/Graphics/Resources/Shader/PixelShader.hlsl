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

float4 main(VSOutput input) : SV_TARGET
{
    float3 normal = normalize(input.Normal);
    float3 lightDir = normalize(-LightData.Direction.xyz);

    // Lambert diffuse
    float diff = max(dot(normal, lightDir), 0.0f);

    float3 finalColor = MaterialData.Ambient.rgb + MaterialData.Diffuse.rgb * diff;

    if (MaterialData.TextureEnable > 0.5f)
    {
        float4 texColor = diffuseTex.Sample(samp, input.Tex);
        finalColor *= texColor.rgb;
    }

    return float4(finalColor, 1.0f);
}
