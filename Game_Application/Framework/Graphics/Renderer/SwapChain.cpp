//==============================================================================
// File        : SwapChain.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SwapChain.h"

#include <dxgi.h>

#include "DebugTool.h"

using namespace Framework;

SwapChain::SwapChain() {};
SwapChain::~SwapChain() {};

bool SwapChain::Initialize(HWND hWnd, ID3D11Device* device) {
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = SCREEN_WIDTH;
    sd.BufferDesc.Height = SCREEN_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ComPtr<IDXGIDevice> dxgiDevice;
    device->QueryInterface(IID_PPV_ARGS(&dxgiDevice));

    ComPtr<IDXGIAdapter> adapter;
    dxgiDevice->GetAdapter(&adapter);

    ComPtr<IDXGIFactory1> factory;
    adapter->GetParent(IID_PPV_ARGS(&factory));

    HRESULT hr = factory->CreateSwapChain(device, &sd, &m_SwapChain);
    if (FAILED(hr)) { return false; }

    LOG_IF(L"SwapChain Initialize Completed");
    return true;
}

void SwapChain::Finalize() {
    m_SwapChain.Reset();
}

void SwapChain::Present() {
    m_SwapChain->Present(1, 0);
}




