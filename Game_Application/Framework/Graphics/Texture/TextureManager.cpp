//==============================================================================
// File        : TextureManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "DebugTool.h"
#include <wincodec.h> 

using namespace Framework;

TextureManager::TextureManager(){}
TextureManager::~TextureManager(){}

bool TextureManager::Initialize() {
    m_Textures.clear();

    LOG_IF(L"TextureManager Initialize Completed");
    return true;
}

void TextureManager::Finalize() {
    LOG_IF(L"TextureManager Finalize..");

    m_Textures.clear();
}

std::shared_ptr<Texture> TextureManager::LoadTexture(const std::wstring& filePath) {
    // すでにロード済みならそれを返す
    auto it = m_Textures.find(filePath);
    if (it != m_Textures.end())
        return it->second;

    // 新規作成してロード
    auto texture = std::make_shared<Texture>();
    if (!texture->Load(filePath))
        return nullptr;

    m_Textures[filePath] = texture;
    return texture;
}

std::shared_ptr<Texture> TextureManager::LoadFromMemory(unsigned char* data, size_t size) {
    int width = 0, height = 0, channels = 0;
    unsigned char* pixels = stbi_load_from_memory(data, static_cast<int>(size), &width, &height, &channels, 4);
    char buf[256];
    sprintf_s(buf, "Loaded texture: %dx%d channels=%d\n", width, height, channels);
    OutputDebugStringA(buf);
    if (!pixels) return nullptr;

    auto texture = std::make_shared<Texture>();
    if (!texture->InitializeFromMemory(pixels, width, height)) {
        stbi_image_free(pixels);
        return nullptr;
    }

    stbi_image_free(pixels);
    return texture;
}

std::shared_ptr<Texture> TextureManager::LoadFromCompressedMemory(const unsigned char* data, size_t size) {
    auto tex = std::make_shared<Texture>();

    IWICImagingFactory* factory = nullptr;
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&factory)
    );
    if (FAILED(hr)) return nullptr;

    IWICStream* stream = nullptr;
    hr = factory->CreateStream(&stream);
    if (FAILED(hr)) { factory->Release(); return nullptr; }

    hr = stream->InitializeFromMemory((BYTE*)data, (DWORD)size);
    if (FAILED(hr)) { stream->Release(); factory->Release(); return nullptr; }

    IWICBitmapDecoder* decoder = nullptr;
    hr = factory->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) { stream->Release(); factory->Release(); return nullptr; }

    IWICBitmapFrameDecode* frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) { decoder->Release(); stream->Release(); factory->Release(); return nullptr; }

    UINT w = 0, h = 0;
    hr = frame->GetSize(&w, &h);
    if (FAILED(hr)) { frame->Release(); decoder->Release(); stream->Release(); factory->Release(); return nullptr; }

    std::vector<BYTE> pixels(w * h * 4);

    IWICFormatConverter* converter = nullptr;
    hr = factory->CreateFormatConverter(&converter);
    if (FAILED(hr)) { frame->Release(); decoder->Release(); stream->Release(); factory->Release(); return nullptr; }

    hr = converter->Initialize(frame, GUID_WICPixelFormat32bppRGBA,
        WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) { converter->Release(); frame->Release(); decoder->Release(); stream->Release(); factory->Release(); return nullptr; }

    hr = converter->CopyPixels(nullptr, w * 4, (UINT)pixels.size(), pixels.data());
    if (FAILED(hr)) { converter->Release(); frame->Release(); decoder->Release(); stream->Release(); factory->Release(); return nullptr; }

    // Texture 作成
    tex->InitializeFromMemory(pixels.data(), w, h);

    // 解放
    converter->Release();
    frame->Release();
    decoder->Release();
    stream->Release();
    factory->Release();

    return tex;
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::wstring& filePath) const {
    auto it = m_Textures.find(filePath);
    if (it != m_Textures.end())
        return it->second;
    return nullptr;
}