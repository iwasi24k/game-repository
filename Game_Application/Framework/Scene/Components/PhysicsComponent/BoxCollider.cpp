//==============================================================================
// File        : BoxCollider.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"

using namespace Framework;

void BoxCollider::Update() {
    auto& tr = GetOwner()->GetTransform();

    // ① ローカルAABB をまず構築
    m_LocalAABB.SetFromCenterAndSize(
        m_PositionOffset,
        m_SizeOffset
    );

    // ② ワールドAABB へ変換：まずスケール適用
    AABB scaled = m_LocalAABB;
    math::vector3f halfSize = (m_LocalAABB.max - m_LocalAABB.min) * 0.5f;
    math::vector3f center = (m_LocalAABB.min + m_LocalAABB.max) * 0.5f;

    halfSize = halfSize * tr.scale;
    center = center * tr.scale;

    scaled.SetFromCenterAndSize(center, halfSize * 2.0f);

    // ③ 位置を適用
    m_WorldAABB = scaled;
    m_WorldAABB.Move(tr.position);
}
