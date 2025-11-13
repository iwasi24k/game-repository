//==============================================================================
// File        : ModelManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-13
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "ModelManager.h"

using namespace Framework;

void ModelManager::Initialize() { m_Models.clear(); }
void ModelManager::Finalize() { m_Models.clear(); }

std::shared_ptr<Model> ModelManager::LoadModel(const std::wstring& path) {
    // ä˘Ç…ì«Ç›çûÇ›çœÇ›Ç»ÇÁÇªÇÍÇï‘Ç∑
    auto it = m_Models.find(path);
    if (it != m_Models.end())
        return it->second;

    // êVãKì«Ç›çûÇ›
    auto model = std::make_shared<Model>();
    if (model->Initialize(path)) {
        m_Models[path] = model;
        return model;
    }

    return nullptr;
}