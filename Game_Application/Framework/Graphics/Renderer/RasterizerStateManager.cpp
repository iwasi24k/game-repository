//==============================================================================
// File        : RasterizerStateManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "RasterizerStateManager.h"

#include "DebugTool.h"

using namespace Framework;

RasterizerStateManager::RasterizerStateManager() {}
RasterizerStateManager::~RasterizerStateManager() {}

bool RasterizerStateManager::Initialize(ID3D11Device* device) {
    D3D11_RASTERIZER_DESC descCull = {};
    descCull.FillMode = D3D11_FILL_SOLID;
    descCull.CullMode = D3D11_CULL_BACK;
    descCull.DepthClipEnable = TRUE;
    descCull.MultisampleEnable = FALSE;

    HRESULT hr = device->CreateRasterizerState(&descCull, &m_CullOnState);
    if (FAILED(hr)) { return false; }

    D3D11_RASTERIZER_DESC descNoCull = descCull;
    descNoCull.CullMode = D3D11_CULL_NONE;

    hr = device->CreateRasterizerState(&descNoCull, &m_CullOffState);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"RasterizerStateManager Initialize Completed");
    return true;
}

void RasterizerStateManager::Finalize() {
    m_CullOnState.Reset();
    m_CullOffState.Reset();
}

void RasterizerStateManager::Apply(ID3D11DeviceContext* context, bool enable) {
    if (enable) 
        context->RSSetState(m_CullOnState.Get());
    else 
        context->RSSetState(m_CullOffState.Get());
}
