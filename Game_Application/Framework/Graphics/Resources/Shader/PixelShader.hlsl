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

float RandomSeed(float3 pos)
{
    return frac(sin(dot(pos.xyz, float3(12.9898, 78.233, 37.719))) * 43758.5453);
}

float SmoothRandom(float3 pos)
{
    float r1 = RandomSeed(pos);
    float r2 = RandomSeed(pos + float3(0.01, 0, 0));
    float r3 = RandomSeed(pos + float3(0, 0.01, 0));
    float r4 = RandomSeed(pos + float3(0, 0, 0.01));
    return (r1 + r2 + r3 + r4) * 0.25; // 平均して滑らかに
}
float4 main(VSPS_Default input) : SV_TARGET
{
    float3 normal = normalize(input.Normal);

    // 太陽光方向
    float3 lightDir = normalize(float3(0.5f, 1.0f, 0.8f));
    float3 viewDir = normalize(float3(0.0f, 0.0f, -1.0f));

    // 上向き補正（太陽光感アップ）
    float shadowFactor = saturate(0.7f + 0.4f * normal.y);

    // 高さ補正と色味補正
    float heightFactor = saturate(0.5 + 0.5 * input.WorldPosition.y / 3.0f); // 0～1
    shadowFactor *= heightFactor; // 高いほど明るく

    float3 heightColor = lerp(float3(0.8, 0.8, 0.8), float3(0.95, 0.95, 0.95), heightFactor); // 高い＝少し黄み、高い位置の強調

    // 滑らかブロックごとの微細陰影
    float variation = SmoothRandom(input.WorldPosition.xyz) * 0.1f + 0.95f; // 0.95～1.05
    shadowFactor *= variation;

    // 拡散反射
    float NdotL = saturate(dot(normal, lightDir));
    float3 diffuse = MaterialData.Diffuse.rgb * LightData.Diffuse.rgb * NdotL * shadowFactor;

    // 環境光
    float3 ambient = MaterialData.Ambient.rgb * LightData.Ambient.rgb * 1.0f;

    // 鏡面反射
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(saturate(dot(viewDir, reflectDir)), MaterialData.Shininess);
    float3 specular = MaterialData.Specular.rgb * spec * shadowFactor;

    // テクスチャ適用
    float3 baseColor = MaterialData.Diffuse.rgb * heightColor;
    if (MaterialData.TextureEnable)
    {
        baseColor *= g_Texture.Sample(g_Sampler, input.TexCoord).rgb;
    }

    // ライティング合成
    float3 finalColor = ambient + diffuse + specular;
    finalColor *= baseColor;

    return float4(finalColor, MaterialData.Diffuse.a);
}
//float4 main(VSPS_Default input) : SV_TARGET
//{
//    float3 normal = normalize(input.Normal);

//    // 太陽光方向
//    float3 lightDir = normalize(float3(-0.5f, 1.0f, 0.9f));
//    float3 viewDir = normalize(float3(0.0f, 0.0f, -1.0f));

//    // 上向き補正
//    float shadowFactor = saturate(0.7f + 0.3f * normal.y);

//    // 高さ補正
//    float heightFactor = saturate(0.5f + 0.5f * (input.WorldPosition.y / 3.0f));
//    shadowFactor *= heightFactor;

//    // 滑らかブロックごとの微細陰影
//    float variation = SmoothRandom(input.WorldPosition.xyz) * 0.1f + 0.95f; // 0.95～1.05
//    shadowFactor *= variation;

//    // 拡散反射
//    float NdotL = saturate(dot(normal, lightDir));
//    float3 diffuse = MaterialData.Diffuse.rgb * LightData.Diffuse.rgb * NdotL * shadowFactor;

//    // 環境光
//    float3 ambient = MaterialData.Ambient.rgb * LightData.Ambient.rgb * 1.0f;

//    // 鏡面反射
//    float3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(saturate(dot(viewDir, reflectDir)), MaterialData.Shininess);
//    float3 specular = MaterialData.Specular.rgb * spec * shadowFactor;

//    // テクスチャ適用
//    float3 baseColor = MaterialData.Diffuse.rgb;
//    if (MaterialData.TextureEnable)
//    {
//        baseColor *= g_Texture.Sample(g_Sampler, input.TexCoord).rgb;
//    }

//    // ライティング合成
//    float3 finalColor = ambient + diffuse + specular;
//    finalColor *= baseColor;

//    return float4(finalColor, MaterialData.Diffuse.a);
//}

//float4 main(VSPS_Default input) : SV_TARGET
//{
//    float3 normal = normalize(input.Normal);

//    // 太陽光方向
//    float3 lightDir = normalize(float3(0.5f, 1.0f, 0.8f));
//    float3 viewDir = normalize(float3(0.0f, 0.0f, -1.0f));

//    // 上向き補正
//    float shadowFactor = saturate(0.7f + 0.3f * normal.y);

//    // 高さ補正
//    float heightFactor = saturate(0.5f + 0.5f * (input.WorldPosition.y / 3.0f));
//    shadowFactor *= heightFactor;

//    // ブロックごと微細な陰影（擬似ランダム）
//    float variation = RandomSeed(input.WorldPosition.xyz) * 0.1f + 0.95f; // 0.95～1.05
//    shadowFactor *= variation;

//    // 拡散反射
//    float NdotL = saturate(dot(normal, lightDir));
//    float3 diffuse = MaterialData.Diffuse.rgb * LightData.Diffuse.rgb * NdotL * shadowFactor;

//    // 環境光
//    float3 ambient = MaterialData.Ambient.rgb * LightData.Ambient.rgb * 1.0f;

//    // 鏡面反射
//    float3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(saturate(dot(viewDir, reflectDir)), MaterialData.Shininess);
//    float3 specular = MaterialData.Specular.rgb * spec * shadowFactor;

//    // テクスチャ適用
//    float3 baseColor = MaterialData.Diffuse.rgb;
//    if (MaterialData.TextureEnable)
//    {
//        baseColor *= g_Texture.Sample(g_Sampler, input.TexCoord).rgb;
//    }

//    // ライティング合成
//    float3 finalColor = ambient + diffuse + specular;
//    finalColor *= baseColor;

//    return float4(finalColor, MaterialData.Diffuse.a);
//}
