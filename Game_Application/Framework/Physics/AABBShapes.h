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

        bool FastIntersect(const AABB& other) const {
            float dx = max.x - other.min.x;
            float dx2 = other.max.x - min.x;
            if (dx < 0.0f || dx2 < 0.0f) return false;

            float dy = max.y - other.min.y;
            float dy2 = other.max.y - min.y;
            if (dy < 0.0f || dy2 < 0.0f) return false;

            float dz = max.z - other.min.z;
            float dz2 = other.max.z - min.z;
            if (dz < 0.0f || dz2 < 0.0f) return false;

            return true;
        }

        // ----------------------------------------
        // 衝突したときに、どのくらい重なっているか（押し戻す量）を返す
        // 正の値ならother側に押す、負の値ならthis側に押す、と考えられる
        math::vector3f GetPenetration(const AABB& other) const {
            // 各方向の重なり量を計算
            float dx1 = other.max.x - min.x; // other → this
            float dx2 = max.x - other.min.x; // this → other
            float dy1 = other.max.y - min.y;
            float dy2 = max.y - other.min.y;
            float dz1 = other.max.z - min.z;
            float dz2 = max.z - other.min.z;

            math::vector3f depth;
            depth.x = (dx1 < dx2) ? dx1 : -dx2; // 小さい方を採用して押し戻す方向を決定
            depth.y = (dy1 < dy2) ? dy1 : -dy2;
            depth.z = (dz1 < dz2) ? dz1 : -dz2;
            return depth;
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
    };
}

#endif // AABB_SHAPES_H