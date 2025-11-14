//==============================================================================
// File        : ModelManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// Overview :
// このクラスは、複数の Model インスタンスを管理します。
// LoadModel() は指定されたファイルパスのモデルを読み込み、
// 既に読み込まれている場合はキャッシュ済みのインスタンスを返します。
// Initialize() と Finalize() により管理対象を初期化・解放可能で、
// メモリ効率の良いモデル再利用を実現します。
//==============================================================================
#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "Model.h"

namespace Framework {

    class ModelManager {
    private:
        std::unordered_map<std::wstring, std::shared_ptr<Model>> m_Models;

        ModelManager() = default;
        ~ModelManager() = default;
		ModelManager(const ModelManager&) = delete;
		ModelManager& operator=(const ModelManager&) = delete;

    public:
        static ModelManager& GetInstance() {
            static ModelManager instance;
            return instance;
        }

        void Initialize();
        void Finalize();

        std::shared_ptr<Model> LoadModel(const std::wstring& path);
    };
}

#endif //MODEL_MANAGER_H