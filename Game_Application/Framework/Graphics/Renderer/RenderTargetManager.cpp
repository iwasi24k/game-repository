//==============================================================================
// File        : RenderTargetManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "RenderTargetManager.h"

#include "Renderer.h"

#include "DebugTool.h"

using namespace Framework;

RenderTargetManager::RenderTargetManager() {}
RenderTargetManager::~RenderTargetManager() {}

// èoóÕêÊÇÃê›íË
bool RenderTargetManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain) {
    ComPtr<ID3D11Texture2D> backBuffer;
    HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));    

    hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView);
    if (FAILED(hr)) { return false; }

    // DepthStencil
    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = SCREEN_WIDTH;
    depthDesc.Height = SCREEN_HEIGHT;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = device->CreateTexture2D(&depthDesc, nullptr, &m_DepthStencilBuffer);
    if (FAILED(hr)) { return false; }

    hr = device->CreateDepthStencilView(m_DepthStencilBuffer.Get(), nullptr, &m_DepthStencilView);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"RenderTargetManager Initialize Completed");
    return true;
}

void RenderTargetManager::Finalize() {
    m_DepthStencilView.Reset();
    m_RenderTargetView.Reset();
    m_DepthStencilBuffer.Reset();
}


void RenderTargetManager::Clear(ID3D11DeviceContext* context, const float clearColor[4]) {
    context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
    context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void RenderTargetManager::Bind(ID3D11DeviceContext* context) {
    context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
}

