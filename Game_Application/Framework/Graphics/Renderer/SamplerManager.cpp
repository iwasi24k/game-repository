//==============================================================================
// File        : SamplerManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SamplerManager.h"

#include "DebugTool.h"

using namespace Framework;

SamplerManager::SamplerManager() {}
SamplerManager::~SamplerManager() {}

// テクスチャの読み方(サンプリング方法)
bool SamplerManager::Initialize(ID3D11Device* device) {
    D3D11_SAMPLER_DESC desc = {};
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
    desc.MaxAnisotropy = 4;

    HRESULT hr = device->CreateSamplerState(&desc, &m_SamplerState);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"SamplerManager Initialize Completed");
    return true;
}

void SamplerManager::Finalize() {
    m_SamplerState.Reset();
}

void SamplerManager::Bind(ID3D11DeviceContext* context) {
    context->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
}

void SamplerManager::SetSampler(UINT slot, ID3D11SamplerState* sampler, ID3D11DeviceContext* context) {
    context->PSSetSamplers(slot, 1, &sampler);
}
