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

bool Texture::Initialize() { return true; }

void Texture::Finalize() {
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

	return true;
}

void Texture::SetSRV(ID3D11ShaderResourceView* srv) { m_ShaderResourceView = srv; }
ID3D11ShaderResourceView* Texture::GetSRV() const { return m_ShaderResourceView.Get(); }
