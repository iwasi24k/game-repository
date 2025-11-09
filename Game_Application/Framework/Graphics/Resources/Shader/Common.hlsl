//==============================================================================
// File        : Common.hlsl
// Description : 共通構造体・定数バッファ定義
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================

cbuffer MatrixBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

struct Light
{
    float4 Direction;       // 光の方向（平行光）
    float4 Diffuse;         // 拡散光
    float4 Ambient;         // 環境光
    float4 Position;        // 点光源の位置
    float4 PointLightParam; // x:有効, y:距離, z:減衰係数など用途自由
};

struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float TextureEnable;
    float3 pad; // 16バイト境界に調整
};

cbuffer LightBuffer : register(b1)
{
    Light LightData;
}

cbuffer MaterialBuffer : register(b2)
{
    Material MaterialData;
}

cbuffer ColorBuffer : register(b3)
{
    float4 Color; // 単色描画用
}

// -------------------------------
// 頂点入力レイアウト構造体群
// -------------------------------
struct VertexInput_Default
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

struct VertexInput_Sprite
{
    float2 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VertexInput_Skinned
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
    uint4 BoneIndices : BLENDINDICES;
    float4 BoneWeights : BLENDWEIGHT;
};

// -------------------------------
// 頂点シェーダ出力／ピクセル入力
// -------------------------------
struct VSOutput
{
    float4 PosH : SV_POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
    float4 Color : COLOR0;
};

struct VertexOutput_Sprite
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};
