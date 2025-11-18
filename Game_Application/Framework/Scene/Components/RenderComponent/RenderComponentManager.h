//==============================================================================
// File        : RenderComponentManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// Overview :
// RenderComponentManager は、GameObject に付随する描画コンポーネントの統括管理を行います。
// 2D スプライトおよび 3D モデルの描画順序をレイヤーで整理し、
// カメラビュー・投影行列を用いた描画制御を一括で実行します。
// レイヤー順に描画を行うことで、重なり順や透過の表現を正しく管理でき、
// 2D/3D を混在させた描画環境を柔軟に構築可能です。
//==============================================================================
#ifndef RENDER_COMPONENT_MANAGER_H
#define RENDER_COMPONENT_MANAGER_H

#include <vector>
#include "GameObject.h"

namespace Framework {

    class RenderComponentManager {
    private:
		GameObject* m_MainCameraObject = nullptr;

    public:
		void Start(std::vector<std::unique_ptr<GameObject>>& gameObjects);
        void Draw(std::vector<std::unique_ptr<GameObject>>& gameObjects);
    };
}

#endif // RENDER_COMPONENT_MANAGER_H