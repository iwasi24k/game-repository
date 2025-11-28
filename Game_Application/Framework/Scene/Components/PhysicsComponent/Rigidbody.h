//==============================================================================
// File        : Rigidbody.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// Overview :
// Rigidbody コンポーネントは、物理運動の計算を担当します。
// AddForce() で加えられた力に基づき加速度を更新し、
// Update() 内で重力や空気抵抗を反映した速度計算、
// そして GameObject の位置更新を毎フレーム実行します。
// これにより、質量・力・速度・加速度の基本的な物理挙動をシンプルに再現します。
//==============================================================================
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Behaviour.h"
#include "MathTransform.h"

namespace Framework {

    struct RigidbodyConfig {
        math::vector3f velocity = math::zero<math::vector3f>();
        float mass = 1.0f;
        bool useGravity = true;
        float gravity = -9.8f;
        float drag = 0.0f;
	};

    class Rigidbody : public Behaviour {
    public:
        math::vector3f m_Velocity = math::zero<math::vector3f>();     // 現在の速度ベクトル
        math::vector3f m_Acceleration = math::zero<math::vector3f>(); // 加速度ベクトル（必要なら）
        float m_Mass = 1.0f;       // 質量（大きいほど慣性が大きくなる）
        bool m_UseGravity = true;  // 重力の影響を受けるかどうか
        float m_Gravity = -9.8f;   // 重力
        float m_Drag = 0.0f;       // 空気抵抗（速度減衰量）

    public:
        void AddForce(const math::vector3f& force);
        void FixedUpdate() override;

		// Getter / Setter
		void SetVelocity(const math::vector3f& velocity) { m_Velocity = velocity; }
		const math::vector3f& GetVelocity() const { return m_Velocity; }
		void SetMass(float mass) { m_Mass = mass; }
		float GetMass() const { return m_Mass; }
		void SetUseGravity(bool useGravity) { m_UseGravity = useGravity; }
		bool IsUseGravity() const { return m_UseGravity; }
		void SetGravity(float gravity) { m_Gravity = gravity; }
		float GetGravity() const { return m_Gravity; }
		void SetDrag(float drag) { m_Drag = drag; }
        float GetDrag() const { return m_Drag; }

	public:
        void Configure(const RigidbodyConfig& config) {
            m_Velocity = config.velocity;
            m_Mass = config.mass;
            m_UseGravity = config.useGravity;
            m_Gravity = config.gravity;
            m_Drag = config.drag;
        }
    };
}

#endif // RIGIDBODY_H