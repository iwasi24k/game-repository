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

    if (!pixels) return nullptr;

    auto texture = std::make_shared<Texture>();
    if (!texture->InitializeFromMemory(pixels, width, height)) {
        stbi_image_free(pixels);
        return nullptr;
    }

    stbi_image_free(pixels);
    return texture;
}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::wstring& filePath) const {
    auto it = m_Textures.find(filePath);
    if (it != m_Textures.end())
        return it->second;
    return nullptr;
}