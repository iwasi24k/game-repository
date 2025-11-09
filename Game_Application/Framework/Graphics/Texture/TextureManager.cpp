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

using namespace Framework;

TextureManager::TextureManager(){}
TextureManager::~TextureManager(){}

bool TextureManager::Initialize() {
    m_Textures.clear();
    return true;
}

void TextureManager::Finalize() {
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

std::shared_ptr<Texture> TextureManager::GetTexture(const std::wstring& filePath) const {
    auto it = m_Textures.find(filePath);
    if (it != m_Textures.end())
        return it->second;
    return nullptr;
}