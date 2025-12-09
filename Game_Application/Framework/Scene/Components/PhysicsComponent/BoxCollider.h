//==============================================================================
// File        : BoxCollider.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
// Overview :
// Framework/Scene/Components/PhysicsComponent/.h
//==============================================================================
#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "ColliderComponent.h"
#include "Framework/Physics/AABBShapes.h"

namespace Framework {

    struct BoxColliderConfig {
        bool isTrigger = false;
        math::vector3f posOffset = math::zero<math::vector3f>();
        math::vector3f sizeOffset = math::zero<math::vector3f>();
    };

    class BoxCollider : public ColliderComponent {
    private:
        AABB m_AABB;

        math::vector3f m_PositionOffset = math::zero<math::vector3f>();
        math::vector3f m_SizeOffset = math::zero<math::vector3f>();

    public:
        void FixedUpdate() override;

        void SetFromTransform(const math::vector3f& position);
        bool Intersect(const ColliderComponent& other) const override;
        math::vector3f GetPenetration(const ColliderComponent& other) const override;
        math::vector3f GetCollisionNormal(const ColliderComponent& other) const override;

        const AABB& GetAABB() const override { return m_AABB; }
        void SetPositionOffset(const math::vector3f& posOffset) { m_PositionOffset = posOffset; }
        const math::vector3f& GetPositionOffset() { return m_PositionOffset; }
        void SetSizeOffset(const math::vector3f& sizeOffset) { m_SizeOffset = sizeOffset; }
        const math::vector3f& GetSizeOffset() { return m_SizeOffset; }
    public:
        void Configure(const BoxColliderConfig& config) {
            m_Type = ColliderType::Box;
            m_IsTrigger = config.isTrigger;
            m_PositionOffset = config.posOffset;
            m_SizeOffset = config.sizeOffset;
        }
    };
}

#endif // BOX_COLLIDER_H