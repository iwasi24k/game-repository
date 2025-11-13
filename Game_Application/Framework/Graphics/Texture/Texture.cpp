//==============================================================================
// File        : Texture.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "Texture.h"
#include <DirectXTex.h>

#include "Renderer.h"
#include "DebugTool.h"

using namespace Framework;

Texture::Texture() {}
Texture::~Texture() {}

bool Texture::Initialize() { 
    LOG_IF(L"TextureManager Initialize Completed");
    return true; 
}

void Texture::Finalize() {
    LOG_IF(L"Texture Finalize..");

	m_ShaderResourceView.Reset();
}

bool Texture::Load(const std::wstring& filePath) {
    auto& renderer = Renderer::GetInstance();
    auto device = renderer.GetDevice();

    // 読み込んだ画像を格納する
    ScratchImage image;
    TexMetadata metadata;

    // WIC対応フォーマット（PNG, JPG, BMPなど）から読み込み
    HRESULT hr = LoadFromWICFile(filePath.c_str(), WIC_FLAGS_NONE, &metadata, image);
    if (FAILED(hr)) {
        LOG_EFF(L"Texture Load Failed: %s", filePath.c_str());
        return false;
    }

    // GPU上にテクスチャを作り、シェーダーから使えるようにする
    hr = CreateShaderResourceView(
        device,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        m_ShaderResourceView.ReleaseAndGetAddressOf()
    );

    if (FAILED(hr)) {
        LOG_EFF(L"Create SRV Failed: %s", filePath.c_str());
        return false;
    }

    LOG_IF(L"Texture Initialize Completed");
	return true;
}

void Texture::SetSRV(ID3D11ShaderResourceView* srv) { m_ShaderResourceView = srv; }
ID3D11ShaderResourceView* Texture::GetSRV() const { return m_ShaderResourceView.Get(); }

bool Texture::InitializeFromMemory(unsigned char* pixelData, int width, int height) {
    if (!pixelData || width <= 0 || height <= 0)
        return false;

    auto& renderer = Renderer::GetInstance();
    auto device = renderer.GetDevice();
    auto context = renderer.GetContext();

    // 既存リソースの解放
    m_ShaderResourceView.Reset();
    m_Texture.Reset();

    // テクスチャ設定
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 0; // 自動ミップ生成対応
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    // 初期データなしで作成（後でUpdateSubresource）
    HRESULT hr = device->CreateTexture2D(&desc, nullptr, m_Texture.GetAddressOf());
    if (FAILED(hr))
        return false;

    // ピクセルデータを書き込み
    context->UpdateSubresource(m_Texture.Get(), 0, nullptr, pixelData, width * 4, 0);

    // シェーダーリソースビュー作成
    hr = device->CreateShaderResourceView(m_Texture.Get(), nullptr, m_ShaderResourceView.GetAddressOf());
    if (FAILED(hr))
        return false;

    // ミップマップ生成
    context->GenerateMips(m_ShaderResourceView.Get());

    return true;
}
