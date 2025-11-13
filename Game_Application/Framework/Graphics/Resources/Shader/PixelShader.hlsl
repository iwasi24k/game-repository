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

float4 main(VSPS_Default input) : SV_TARGET
{
    // 正規化法線
    float3 normal = normalize(input.Normal);

    // 光の方向（平行光）
    float3 lightDir = normalize(-LightData.Direction.xyz);

    // ビュー方向（仮：Z前方からの視点）
    float3 viewDir = normalize(float3(0.0f, 0.0f, -1.0f));

    // 拡散反射
    float NdotL = saturate(dot(normal, lightDir));
    float3 diffuse = MaterialData.Diffuse.rgb * LightData.Diffuse.rgb * NdotL;

    // 環境光
    float3 ambient = MaterialData.Ambient.rgb * LightData.Ambient.rgb;

    // 鏡面反射
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(saturate(dot(viewDir, reflectDir)), MaterialData.Shininess);
    float3 specular = MaterialData.Specular.rgb * spec;

    // ベースカラー
    float3 baseColor = MaterialData.Diffuse.rgb;

    // テクスチャ適用（有効時）
    if (MaterialData.TextureEnable)
    {
        baseColor = g_Texture.Sample(g_Sampler, input.TexCoord).rgb;
    }

    // 合成
    float3 finalColor = ambient + diffuse + specular;
    finalColor *= baseColor;

    //return float4(finalColor, MaterialData.Diffuse.a);
    //return float4(1.0f, 0.0f, 0.0f, 1.0f);
    return float4(baseColor, Color.a);
}
