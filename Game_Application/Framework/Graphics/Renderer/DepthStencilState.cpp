//==============================================================================
// File        : DepthStencilState.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "DepthStencilState.h"

#include "DebugTool.h"

using namespace Framework;

DepthStencilState::DepthStencilState() {}
DepthStencilState::~DepthStencilState() {}

// 奥行情報
bool DepthStencilState::Initialize(ID3D11Device* device) {
    // 深度テスト有効ステート
    D3D11_DEPTH_STENCIL_DESC descEnabled = {};
    descEnabled.DepthEnable = TRUE;
    descEnabled.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    descEnabled.DepthFunc = D3D11_COMPARISON_LESS;
    descEnabled.StencilEnable = FALSE;

    HRESULT hr = device->CreateDepthStencilState(&descEnabled, &m_DepthEnabledState);
    if (FAILED(hr)) { return false; }

    // 深度テスト無効ステート
    D3D11_DEPTH_STENCIL_DESC descDisabled = {};
    descDisabled.DepthEnable = FALSE;
    descDisabled.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    descDisabled.DepthFunc = D3D11_COMPARISON_LESS;
    descDisabled.StencilEnable = FALSE;

    hr = device->CreateDepthStencilState(&descDisabled, &m_DepthDisabledState);
    if (FAILED(hr)) { return false; }

    descDisabled.DepthEnable = TRUE;

    hr = device->CreateDepthStencilState(&descDisabled, &m_DepthEnabledNoWriteState);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"DepthStencilState Initialize Completed");
    return true;
}

void DepthStencilState::Finalize() {
    m_DepthEnabledState.Reset();
    m_DepthDisabledState.Reset();
}

void DepthStencilState::Bind(ID3D11DeviceContext* context, bool enable) {
    if (enable)
        context->OMSetDepthStencilState(m_DepthEnabledState.Get(), 0);
    else
        context->OMSetDepthStencilState(m_DepthDisabledState.Get(), 0);
}

void DepthStencilState::WriteBind(ID3D11DeviceContext* context, bool enable) {
    if (enable)
        context->OMSetDepthStencilState(m_DepthEnabledState.Get(), 0);
    else
        context->OMSetDepthStencilState(m_DepthEnabledNoWriteState.Get(), 0);
}
