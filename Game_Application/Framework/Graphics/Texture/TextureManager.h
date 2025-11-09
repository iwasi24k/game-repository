//==============================================================================
// File        : TextureManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 における複数テクスチャの管理を担当します。
// ファイルパスをキーにしてテクスチャをキャッシュし、重複ロードを防止。
// LoadTexture() で未登録テクスチャを読み込み、登録済みなら既存のものを返却。
// GetTexture() で既存テクスチャへのアクセスが可能。
// Initialize()/Finalize() で管理マップを初期化・解放し、メモリの安全性を確保。
// これにより、描画中に同一テクスチャを何度も読み込む無駄を排除できます。
//==============================================================================
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include "Texture.h"

namespace Framework {

    class TextureManager {
    private:
        std::unordered_map<std::wstring, std::shared_ptr<Texture>> m_Textures;

        TextureManager();
        ~TextureManager();
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;

    public:
        static TextureManager& GetInstance() {
            static TextureManager instance;
            return instance;
        }

        bool Initialize();
        void Finalize();

        std::shared_ptr<Texture> LoadTexture(const std::wstring& filePath);
        std::shared_ptr<Texture> GetTexture(const std::wstring& filePath) const;
    };

}

#endif // TEXTURE_MANAGER_H