//==============================================================================
// File        : BlendStateManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "BlendStateManager.h"

#include "DebugTool.h"

using namespace Framework;

BlendStateManager::BlendStateManager() {}
BlendStateManager::~BlendStateManager() {}

bool BlendStateManager::Initialize(ID3D11Device* device) {
    D3D11_BLEND_DESC desc = {};
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;

    auto& rt = desc.RenderTarget[0];
    rt.BlendEnable = TRUE;
    rt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    rt.BlendOp = D3D11_BLEND_OP_ADD;
    rt.SrcBlendAlpha = D3D11_BLEND_ONE;
    rt.DestBlendAlpha = D3D11_BLEND_ZERO;
    rt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    HRESULT hr = device->CreateBlendState(&desc, &m_BlendState);
    if (FAILED(hr)) { return false; }

    desc.AlphaToCoverageEnable = TRUE;

    hr = device->CreateBlendState(&desc, &m_BlendStateATC);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"BlendStateManager Initialize Completed");
    return true;
}

void BlendStateManager::Finalize() {
    m_BlendState.Reset();
    m_BlendStateATC.Reset();
}

void BlendStateManager::Apply(ID3D11DeviceContext* context, bool useAlphaToCoverage) {
    float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
    UINT sampleMask = 0xffffffff;

    ID3D11BlendState* blendState = nullptr;

    if (useAlphaToCoverage)
        blendState = m_BlendStateATC.Get();
    else
        blendState = m_BlendState.Get();

    context->OMSetBlendState(blendState, blendFactor, sampleMask);
}
