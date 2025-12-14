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

#include "SceneManager.h"
#include "GameObject.h"
#include "ModelComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Components/CameraComponent/Camera.h"

using namespace Framework;

void RenderComponentManager::Start(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    m_MainCameraObject = SceneManager::GetInstance().GetCurrentScene()->GetGameObjectManager()->FindObject("MainCamera");
}

void RenderComponentManager::Draw(std::vector<std::unique_ptr<GameObject>>& gameObjects) {
	auto mainCamera = m_MainCameraObject->GetComponent<Camera>();
    math::matrix view = mainCamera->GetView();
    math::matrix proj = mainCamera->GetProjection();

    // 共通RenderItem
    struct RenderItem {
        RenderComponent* comp;
        float layer;
        bool is3D;   // Model: true / Sprite: false
    };

    std::vector<RenderItem> renderQueue;

    for (const auto& obj : gameObjects) {
        if (!obj->IsActive()) continue;
        auto sprite = obj->GetComponent<SpriteComponent>();
        if (!sprite) {
            if (!mainCamera->IsSphereVisible(obj->GetTransform().position, obj->GetTransform().scale.x))
                continue;
        }
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
        if (sprite) {
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
