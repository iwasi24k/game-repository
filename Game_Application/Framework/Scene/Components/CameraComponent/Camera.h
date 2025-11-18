//==============================================================================
// File        : Camera.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef CAMERA_H
#define CAMERA_H

#include "Behaviour.h"
#include "MathTransform.h"

namespace Framework {

	enum class ProjectionType {
		Perspective,
		Orthographic
	};

	class Camera : public Behaviour {
	protected:
		math::matrix m_View{};
		math::matrix m_Projection{};
		math::matrix m_ViewProjection{};

		ProjectionType m_ProjectionType = ProjectionType::Perspective;
		float m_FOVY = DirectX::XM_PIDIV4; // 45 degrees
		float m_AspectRatio = 16.0f / 9.0f;
		float m_NearZ = 0.1f;
		float m_FarZ = 1000.0f;
		float m_OrthoWidth = 10.0f;
		float m_OrthoHeight = 10.0f;

	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual void Awake() override {
			// èâä˙ìäâeçsóÒÇÃê›íË
			if (m_ProjectionType == ProjectionType::Perspective) {
				SetPerspective(m_FOVY, m_AspectRatio, m_NearZ, m_FarZ);
			}
			else {
				SetOrthographic(m_OrthoWidth, m_OrthoHeight, m_NearZ, m_FarZ);
			}
		}
		virtual void Update() override = 0;
		virtual void SetPerspective(float fovY, float aspect, float nearZ, float farZ) {
			m_ProjectionType = ProjectionType::Perspective;
			m_FOVY = fovY;
			m_AspectRatio = aspect;
			m_NearZ = nearZ;
			m_FarZ = farZ;
			m_Projection = math::matrix::PerspectiveFovLH(fovY, aspect, nearZ, farZ);
		}
		virtual void SetOrthographic(float width, float height, float nearZ, float farZ) {
			m_ProjectionType = ProjectionType::Orthographic;
			m_OrthoWidth = width;
			m_OrthoHeight = height;
			m_NearZ = nearZ;
			m_FarZ = farZ;
			m_Projection = math::matrix::OrthographicLH(width, height, nearZ, farZ);
		}

		virtual const math::matrix& GetView() const { return m_View; }
		virtual const math::matrix& GetProjection() const { return m_Projection; }
		virtual math::matrix GetViewProjection() const { return m_ViewProjection; }

	};
} // namespace Framework


#endif // CAMERA_H
