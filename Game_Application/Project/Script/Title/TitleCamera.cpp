//==============================================================================
// File        : TitleCamera.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "TitleCamera.h"
#include "GameObject.h"
#include "../../Core/Timer.h"

using namespace Framework;

void TitleCamera::Start() {
    math::matrix rot =
        math::matrix::RotationX(m_Rotation.x) *
        math::matrix::RotationY(m_Rotation.y);

    // --- 前方向(Z-)を回転させてカメラの向きに ---
    math::vector3f forward = rot.TransformVector({ 0, 0, -1 });

    // --- 注視点（m_Focus）から一定距離後ろに配置 ---
    float distance = m_Distance; // 任意の距離
    math::vector3f camPos = m_Focus - forward * distance;

    GetOwner()->GetTransform().position = camPos;

    // --- View 更新 ---
    UpdateView(camPos, m_Focus);
}
void TitleCamera::Update() {
}