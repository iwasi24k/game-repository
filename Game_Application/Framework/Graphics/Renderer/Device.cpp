//==============================================================================
// File        : Device.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Device.h"

#include <dxgi.h>
#include <dxgi1_2.h>

#include "DebugTool.h"

using namespace Framework;

Device::Device() {}
Device::~Device() {}

bool Device::Initialize() {
    UINT createDeviceFlags = 0;

#if defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // 上から順に対応しているGPUの機能を選択
    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDevice(
        nullptr,                    // アダプタ（nullptr = デフォルト）
        D3D_DRIVER_TYPE_HARDWARE,   // ドライバタイプ
        nullptr,                    // ソフトウェア（使わない）
        createDeviceFlags,          // フラグ
        featureLevels,              // サポートレベル => 検索
        ARRAYSIZE(featureLevels),   // レベル数
        D3D11_SDK_VERSION,          // SDKバージョン
        m_Device.GetAddressOf(),    // デバイスの出力先
        &featureLevel,              // 実際に使われたレベル
        m_Context.GetAddressOf()    // コンテキストの出力先
    );

    if (FAILED(hr)) { return false; }

    LOG_IF(L"Device Initialize Completed");
    return true;
}

void Device::Finalize() {
    m_Context.Reset();
    m_Device.Reset();
}
