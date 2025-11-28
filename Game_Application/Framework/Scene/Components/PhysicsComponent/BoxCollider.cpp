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

void BoxCollider::FixedUpdate() {

}

void BoxCollider::SetFromTransform(const math::vector3f& position) {
	auto t = GetOwner()->GetTransform();
	t.scale = t.scale + m_SizeOffset;
	t.position = position + m_PositionOffset;
	m_AABB.SetFromCenterAndSize(t.position, t.scale);
}

bool BoxCollider::Intersect(const ColliderComponent& other) const {
    if (other.GetType() == ColliderType::Box) {
        const BoxCollider& box = static_cast<const BoxCollider&>(other);
        return m_AABB.Intersect(box.m_AABB);
    }
    return false;
}

math::vector3f BoxCollider::GetPenetration(const ColliderComponent& other) const {
    if (other.GetType() == ColliderType::Box) {
        const BoxCollider& box = static_cast<const BoxCollider&>(other);
        return m_AABB.GetPenetration(box.m_AABB);
    }
    return { 0,0,0 };
}

math::vector3f BoxCollider::GetCollisionNormal(const ColliderComponent& other) const {
	if (other.GetType() == ColliderType::Box) {
		const BoxCollider& o = static_cast<const BoxCollider&>(other);

		math::vector3f pen = m_AABB.GetPenetration(o.m_AABB);

		float ax = std::fabs(pen.x);
		float ay = std::fabs(pen.y);
		float az = std::fabs(pen.z);

		if (ax <= ay && ax <= az) {
			return math::vector3f{ (pen.x > 0.0f) ? 1.0f : -1.0f, 0.0f, 0.0f };
		}
		if (ay <= ax && ay <= az) {
			return math::vector3f{ 0.0f, (pen.y > 0.0f) ? 1.0f : -1.0f, 0.0f };
		}
		// else z ‚ªÅ¬
		return math::vector3f{ 0.0f, 0.0f, (pen.z > 0.0f) ? 1.0f : -1.0f };
	}

	return ColliderComponent::GetCollisionNormal(other);
}