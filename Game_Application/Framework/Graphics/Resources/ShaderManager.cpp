//==============================================================================
// File        : ShaderManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ShaderManager.h"
#include <fstream> // ファイル読み込み用#include "Window.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "DebugTool.h"

using namespace Framework;

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

bool ShaderManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* context) {
    m_Device = device;
    m_Context = context;

    LOG_IF(L"ShaderManager Initialize Completed");

    return true;
}

void ShaderManager::Finalize() {
    LOG_IF(L"ShaderManager Shutdown..");
    m_VertexShaders.clear();
    m_PixelShaders.clear();
    m_InputLayouts.clear();
    m_Device = nullptr;
	m_Context = nullptr;
}

void ShaderManager::SetShader(const std::wstring& name) {
    auto itVS = m_VertexShaders.find(name);
    auto itPS = m_PixelShaders.find(name);
    auto itLayout = m_InputLayouts.find(name);

    if (itVS != m_VertexShaders.end() &&
        itPS != m_PixelShaders.end() &&
        itLayout != m_InputLayouts.end()) {
        m_Context->IASetInputLayout(itLayout->second.Get());
        m_Context->VSSetShader(itVS->second.Get(), nullptr, 0);
        m_Context->PSSetShader(itPS->second.Get(), nullptr, 0);
    }
    else {
        // デバッグ用にエラーメッセージ
        LOG_EFF(L"[ShaderManager] Shader not found: " + name);
    }
}

void ShaderManager::SetTexture(UINT slot, ID3D11ShaderResourceView* texture) {
    m_Context->PSSetShaderResources(slot, 1, &texture);
}

bool ShaderManager::LoadShaderFile(const std::wstring& path, std::vector<char>& outShaderData) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        LOG_EFF(L"[ShaderManager] Failed to open shader file: " + path);
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(file.tellg());
    if (size == 0) {
        LOG_EFF(L"[ShaderManager] Shader file is empty: " + path);
        return false;
    }

    file.seekg(0, std::ios::beg);
    outShaderData.resize(size);
    file.read(outShaderData.data(), size);
    return true;
}

void ShaderManager::LoadVS(const std::wstring& name, const std::wstring& vsPath, Shader::VertexLayoutType layoutType) {
    std::vector<char> vsData;
    if (!LoadShaderFile(vsPath, vsData)) return;

    ComPtr<ID3D11VertexShader> vs;
    if (FAILED(m_Device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vs))) {
        LOG_EFF(L"[ShaderManager] Failed to create vertex shader: " + name);
        return;
    }

    ComPtr<ID3D11InputLayout> layout;
    if (!CreateInputLayoutByType(layoutType, vsData.data(), vsData.size(), layout)) {
        LOG_EFF(L"[ShaderManager] Failed to create input layout: " + name);
        return;
    }

    m_VertexShaders[name] = vs;
    m_InputLayouts[name] = layout;
}

void Framework::ShaderManager::LoadPS(const std::wstring& name, const std::wstring& psPath) {
    std::vector<char> psData;
    if (!LoadShaderFile(psPath, psData)) return;

    ComPtr<ID3D11PixelShader> ps;
    if (FAILED(m_Device->CreatePixelShader(psData.data(), psData.size(), nullptr, &ps))) {
        LOG_EFF(L"[ShaderManager] Failed to create pixel shader: " + name);
        return;
    }

    m_PixelShaders[name] = ps;
}


bool ShaderManager::CreateInputLayoutByType(Shader::VertexLayoutType type,
    const void* vsData, size_t vsSize,
    ComPtr<ID3D11InputLayout>& layout)
{
    std::vector<D3D11_INPUT_ELEMENT_DESC> descs;

    switch (type) {
    case Shader::VertexLayoutType::Default:
        descs = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(Shader::Vertex, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(Shader::Vertex, Normal),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Shader::Vertex, Diffuse),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, offsetof(Shader::Vertex, TexCoord), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        break;

    case Shader::VertexLayoutType::Sprite:
        descs = {
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        break;

    case Shader::VertexLayoutType::Skinned:
        descs = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Shader::SkinnedVertex, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Shader::SkinnedVertex, Normal),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(Shader::SkinnedVertex, TexCoord), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, offsetof(Shader::SkinnedVertex, BoneIndices), D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Shader::SkinnedVertex, BoneWeights), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        break;

    default:
        LOG_EFF(L"[ShaderManager] Unknown VertexLayoutType");
        return false;

    }

    HRESULT hr = m_Device->CreateInputLayout(
        descs.data(), static_cast<UINT>(descs.size()),
        vsData, vsSize,
        &layout
    );
    return SUCCEEDED(hr);
}