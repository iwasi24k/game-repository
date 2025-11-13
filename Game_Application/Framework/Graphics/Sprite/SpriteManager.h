//==============================================================================
// File        : SpriteManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// Overview :
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
        SpriteManager() = default;
        ~SpriteManager() = default;

        std::unordered_map<std::wstring, std::shared_ptr<Sprite>> m_Sprites;

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