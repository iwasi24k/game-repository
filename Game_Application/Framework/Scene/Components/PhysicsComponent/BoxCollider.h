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

    class BoxCollider : public ColliderComponent {
    private:
        AABB m_LocalAABB;
        AABB m_WorldAABB;

        math::vector3f m_PositionOffset = math::zero<math::vector3f>();
        math::vector3f m_SizeOffset = math::zero<math::vector3f>();

    public:
        void Update() override;

        const AABB& GetWorldAABB() const { return m_WorldAABB; }
        void SetPositionOffset(const math::vector3f& posOffset) { m_PositionOffset = posOffset; }
        const math::vector3f& GetPositionOffset() { return m_PositionOffset; }
        void SetSizeOffset(const math::vector3f& sizeOffset) { m_SizeOffset = sizeOffset; }
        const math::vector3f& GetSizeOffset() { return m_SizeOffset; }

    public:
        void Configure(const math::vector3f& posOffset, const math::vector3f& sizeOffset) {
            m_PositionOffset = posOffset;
            m_SizeOffset = sizeOffset;
        }
    };
}

#endif // BOX_COLLIDER_H