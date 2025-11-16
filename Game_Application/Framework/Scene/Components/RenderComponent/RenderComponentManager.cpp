//==============================================================================
// File        : RenderComponentManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "RenderComponentManager.h"

#include "GameObject.h"
#include "ModelComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"

using namespace Framework;

void RenderComponentManager::Draw(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    math::matrix view = math::matrix::LookAtLH(
        { 0.0f, 0.0f, -5.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f }
    );
    math::matrix proj = math::matrix::PerspectiveFovLH(
        DirectX::XMConvertToRadians(60.0f),
        static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
        0.1f, 100.0f
    );

    // 共通RenderItem
    struct RenderItem {
        RenderComponent* comp;
        float layer;
        bool is3D;   // Model: true / Sprite: false
    };

    std::vector<RenderItem> renderQueue;

    for (const auto& obj : gameObjects) {
        if (!obj->IsActive()) continue;

        // ModelComponent
        if (auto model = obj->GetComponent<ModelComponent>()) {
            model->SetTransform(
                obj->GetTransform().position,
                obj->GetTransform().scale,
                obj->GetTransform().rotation
            );
            renderQueue.push_back({ model, model->GetLayer(), true });
        }

        // SpriteComponent
        if (auto sprite = obj->GetComponent<SpriteComponent>()) {
            sprite->SetTransform(
                obj->GetTransform().position,
                obj->GetTransform().scale,
                obj->GetTransform().rotation
            );
            renderQueue.push_back({ sprite, sprite->GetLayer(), false });
        }
    }

    // レイヤーソート（昇順）
    std::sort(renderQueue.begin(), renderQueue.end(),
        [](const RenderItem& a, const RenderItem& b) {
            return a.layer < b.layer;
        }
    );

    // 描画
    for (auto& item : renderQueue) {
        if (item.is3D) {
            Renderer::GetInstance().SetDepthEnable(true);
            item.comp->Draw(view, proj);
        }
        else {
            Renderer::GetInstance().SetDepthEnable(false);
            item.comp->Draw();
        }
    }
}
