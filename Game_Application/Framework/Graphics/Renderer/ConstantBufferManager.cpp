//==============================================================================
// File        : ConstantBufferManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ConstantBufferManager.h"

#include "DebugTool.h"

using namespace Framework;

ConstantBufferManager::ConstantBufferManager() {}
ConstantBufferManager::~ConstantBufferManager() {}

bool ConstantBufferManager::Initialize(ID3D11Device* device) {
    m_Device = device;

    LOG_IF(L"ConstantBufferManager Initialize Completed");
    return true;
}

void ConstantBufferManager::Finalize() {
    m_Buffer.clear();
}

