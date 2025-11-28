//==============================================================================
// File        : Collider.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-26
// Last Update : 2025-11-26
//------------------------------------------------------------------------------
// Overview :
// Framework/Scene/Components/PhysicsComponent/.h
//==============================================================================
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Behaviour.h"
#include "MathTransform.h"

namespace Framework {

    enum class ColliderType { Box, Sphere, Capsule, Mesh };

    class ColliderComponent : public Behaviour {
    protected:
        bool m_IsTrigger = false;
        ColliderType m_Type;

    public:
        virtual void FixedUpdate() override = 0;

        virtual void SetFromTransform(const math::vector3f& position) = 0;
        virtual bool Intersect(const ColliderComponent& other) const = 0;
        virtual math::vector3f GetPenetration(const ColliderComponent& other) const = 0;
        virtual math::vector3f GetCollisionNormal(const ColliderComponent& other) const {
            math::vector3f pen = GetPenetration(other);
            float len2 = pen.x * pen.x + pen.y * pen.y + pen.z * pen.z;
            if (len2 <= 1e-8f) return math::vector3f{ 0.0f, 0.0f, 0.0f };
            float invLen = 1.0f / std::sqrt(len2);
            return pen * invLen;
        }

        [[nodiscard]] ColliderType GetType() const noexcept { return m_Type; }
        [[nodiscard]] bool IsTrigger() const noexcept { return m_IsTrigger; }
    };
}

#endif // COLLIDER_H