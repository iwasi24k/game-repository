//==============================================================================
// File        : ViewportManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ViewportManager.h"

#include "DebugTool.h"

using namespace Framework;

ViewportManager::ViewportManager() {}
ViewportManager::~ViewportManager() {}

bool ViewportManager::Initialize() {
    // ビューポート設定
    m_Viewport.Width = static_cast<FLOAT>(SCREEN_WIDTH);
    m_Viewport.Height = static_cast<FLOAT>(SCREEN_HEIGHT);
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;

    LOG_IF(L"ViewportManager Initialize Completed");
    return true;
}

void ViewportManager::Finalize(){}

void ViewportManager::Bind(ID3D11DeviceContext* context) {
    context->RSSetViewports(1, &m_Viewport);
}
