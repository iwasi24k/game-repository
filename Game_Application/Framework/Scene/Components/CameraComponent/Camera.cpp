//==============================================================================
// File        : Camera.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-08
// Last Update : 2025-12-08
//------------------------------------------------------------------------------
// Overview :
// Camera クラスはシーン内の視点（カメラ）を管理するコンポーネントです。
// ビュー行列と投影行列を保持し、Perspective（透視投影）とOrthographic（正射影）の切り替えが可能です。
// Awake() で初期投影行列を設定し、Update() でカメラの動きやビュー行列を更新します。
// これにより、3D/2D 空間でのシーン描画に必要な視点変換を統合的に提供します。
//==============================================================================
#include "pch.h"
#include "Camera.h"

using namespace Framework;

void Camera::ExtractFrustumPlanes() {
    // ViewProjection を float4x4 に取り出す
    DirectX::XMFLOAT4X4 mat{};
    DirectX::XMStoreFloat4x4(&mat, m_ViewProjection.ToXMMATRIX());

    auto A = [&](int r, int c) -> float {
        return *((&mat.m[0][0]) + (r * 4 + c));
        };

    // 左平面
    m_FrustumPlanes[0] = {
        A(0,3) + A(0,0),
        A(1,3) + A(1,0),
        A(2,3) + A(2,0),
        A(3,3) + A(3,0)
    };

    // 右平面
    m_FrustumPlanes[1] = {
        A(0,3) - A(0,0),
        A(1,3) - A(1,0),
        A(2,3) - A(2,0),
        A(3,3) - A(3,0)
    };

    // 下平面
    m_FrustumPlanes[2] = {
        A(0,3) + A(0,1),
        A(1,3) + A(1,1),
        A(2,3) + A(2,1),
        A(3,3) + A(3,1)
    };

    // 上平面
    m_FrustumPlanes[3] = {
        A(0,3) - A(0,1),
        A(1,3) - A(1,1),
        A(2,3) - A(2,1),
        A(3,3) - A(3,1)
    };

    // 近平面
    m_FrustumPlanes[4] = {
        A(0,3) + A(0,2),
        A(1,3) + A(1,2),
        A(2,3) + A(2,2),
        A(3,3) + A(3,2)
    };

    // 遠平面
    m_FrustumPlanes[5] = {
        A(0,3) - A(0,2),
        A(1,3) - A(1,2),
        A(2,3) - A(2,2),
        A(3,3) - A(3,2)
    };

    // 正規化
    for (int i = 0; i < 6; ++i) {
        math::vector3f n = {
            m_FrustumPlanes[i].x,
            m_FrustumPlanes[i].y,
            m_FrustumPlanes[i].z
        };
        float len = n.length();
        if (len > 0.0f) {
            m_FrustumPlanes[i] /= len;
        }
    }
}

bool Camera::IsSphereVisible(const math::vector3f& center, float radius) const {
    for (int i = 0; i < 6; ++i) {
        const auto& p = m_FrustumPlanes[i];

        // 平面: Ax + By + Cz + D
        float dist = p.x * center.x + p.y * center.y + p.z * center.z + p.w;

        // 中心 + 半径 が平面の外側なら不可視
        if (dist < -radius) {
            return false;
        }
    }
    return true;
}
