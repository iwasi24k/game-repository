//==============================================================================
// File        : ModelManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// Overview :
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
        ModelManager() = default;
        ~ModelManager() = default;

        std::unordered_map<std::wstring, std::shared_ptr<Model>> m_Models;

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