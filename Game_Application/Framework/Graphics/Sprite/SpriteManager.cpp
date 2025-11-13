//==============================================================================
// File        : SpriteManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "SpriteManager.h"

#include "DebugTool.h"

using namespace Framework;

void SpriteManager::Initialize() { m_Sprites.clear(); }
void SpriteManager::Finalize() { m_Sprites.clear(); }

std::shared_ptr<Sprite> SpriteManager::LoadSprite(const std::wstring& texturePath) {
    // 既にロード済みならそれを返す
    auto it = m_Sprites.find(texturePath);
    if (it != m_Sprites.end())
        return it->second;

    // 新規作成
    auto sprite = std::make_shared<Sprite>();
    if (!sprite->Initialize()) return nullptr;

    // テクスチャをロードして設定
    auto texture = TextureManager::GetInstance().LoadTexture(texturePath);
    sprite->SetTexture(texture);

    m_Sprites[texturePath] = sprite;
    return sprite;
}
