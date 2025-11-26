//==============================================================================
// File        : AABBShapes.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef AABB_SHAPES_H
#define AABB_SHAPES_H

#include "MathTransform.h"

#undef min
#undef max

namespace Framework {

    struct AABB {
        // 箱（Axis-Aligned Bounding Box）の空間上の範囲を表す2点
        math::vector3f min; // 箱の左下前の角（最小座標）
        math::vector3f max; // 箱の右上奥の角（最大座標）

        // デフォルトコンストラクタ（何もしない）
        AABB() = default;

        // minとmaxを指定して初期化するコンストラクタ
        AABB(const math::vector3f& min_, const math::vector3f& max_) : min(min_), max(max_) {}

        // ----------------------------------------
        // 中心座標とサイズから、minとmaxを計算して箱を作る
        // 例えば、ゲームオブジェクトの位置と大きさから当たり判定を作るときに便利
        void SetFromCenterAndSize(const math::vector3f& center, const math::vector3f& size) {
            math::vector3f half = size * 0.5f; // サイズの半分
            min = center - half; // 箱の最小座標
            max = center + half; // 箱の最大座標
        }

        // ----------------------------------------
        // 箱を空間上で移動させる
        // 当たり判定をオブジェクトの少し上や横にずらしたい場合に使える
        void Move(const math::vector3f& offset) {
            min += offset; // 最小座標を移動
            max += offset; // 最大座標を移動
        }

        // ----------------------------------------
        // 2つの箱が重なっているか（衝突しているか）判定する
        bool Intersect(const AABB& other) const {
            // 各軸ごとに重なっているかチェック
            return (max.x >= other.min.x && min.x <= other.max.x) &&
                (max.y >= other.min.y && min.y <= other.max.y) &&
                (max.z >= other.min.z && min.z <= other.max.z);
        }

        // ----------------------------------------
        // 衝突したときに、どのくらい重なっているか（押し戻す量）を返す
        // 正の値ならother側に押す、負の値ならthis側に押す、と考えられる
        math::vector3f GetPenetration(const AABB& other) const {
            float overlapX = std::min(max.x - other.min.x, other.max.x - min.x);
            float overlapY = std::min(max.y - other.min.y, other.max.y - min.y);
            float overlapZ = std::min(max.z - other.min.z, other.max.z - min.z);

            // 絶対値が最も小さい軸のみ採用
            math::vector3f push;

            if (overlapX <= overlapY && overlapX <= overlapZ) {
                // X 軸
                push = { (max.x < other.max.x) ? -overlapX : overlapX, 0, 0 };
            }
            else if (overlapY <= overlapX && overlapY <= overlapZ) {
                // Y 軸
                push = { 0, (max.y < other.max.y) ? -overlapY : overlapY, 0 };
            }
            else {
                // Z 軸
                push = { 0, 0, (max.z < other.max.z) ? -overlapZ : overlapZ };
            }

            return push;
        }

        // ----------------------------------------
        // 箱の中に点（中心座標）が含まれているか判定する
        // 例えば「プレイヤーがトリガー範囲に入ったか」などに使える
        bool Contains(const math::vector3f& point) const {
            return (point.x >= min.x && point.x <= max.x) &&
                (point.y >= min.y && point.y <= max.y) &&
                (point.z >= min.z && point.z <= max.z);
        }

        math::vector3f Center() const {
            return (min + max) * 0.5f;
        }

        static bool ComputePush(const AABB& a, const AABB& b, math::vector3f& outPush) {
            if (!a.Intersect(b)) {
                outPush = { 0, 0, 0 };
                return false;
            }

            float overlapX = std::min(a.max.x, b.max.x) - std::max(a.min.x, b.min.x);
            float overlapY = std::min(a.max.y, b.max.y) - std::max(a.min.y, b.min.y);
            float overlapZ = std::min(a.max.z, b.max.z) - std::max(a.min.z, b.min.z);

            float minOverlap = std::min({ overlapX, overlapY, overlapZ });

            // X軸が最小
            if (minOverlap == overlapX) {
                if (a.Center().x < b.Center().x)
                    outPush = { -overlapX, 0, 0 };
                else
                    outPush = { overlapX, 0, 0 };
            }
            // Y軸が最小
            else if (minOverlap == overlapY) {
                if (a.Center().y < b.Center().y)
                    outPush = { 0, -overlapY, 0 };
                else
                    outPush = { 0, overlapY, 0 };
            }
            // Z軸が最小
            else {
                if (a.Center().z < b.Center().z)
                    outPush = { 0, 0, -overlapZ };
                else
                    outPush = { 0, 0, overlapZ };
            }

            return true;
        }
    };
}

#endif // AABB_SHAPES_H