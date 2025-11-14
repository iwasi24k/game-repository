//==============================================================================
// File        : SpriteManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// Overview :
// このクラスは、2D スプライトの生成と管理を統括します。
// LoadSprite() は指定されたテクスチャパスからスプライトを生成し、
// 既に存在する場合はキャッシュ済みのインスタンスを返します。
// Initialize() と Finalize() により管理対象を初期化・解放可能で、
// 無駄なスプライトの再生成を防ぎ、描画リソースを効率化します。
//==============================================================================
#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "Sprite.h"
#include "TextureManager.h"

namespace Framework {

    class SpriteManager {
    private:
        std::unordered_map<std::wstring, std::shared_ptr<Sprite>> m_Sprites;

        SpriteManager() = default;
        ~SpriteManager() = default;
		SpriteManager(const SpriteManager&) = delete;
		SpriteManager& operator=(const SpriteManager&) = delete;

    public:
        static SpriteManager& GetInstance() {
            static SpriteManager instance;
            return instance;
        }

        void Initialize();
        void Finalize();

        std::shared_ptr<Sprite> LoadSprite(const std::wstring& texturePath);
    };
}

#endif //SPRITE_MANAGER_H