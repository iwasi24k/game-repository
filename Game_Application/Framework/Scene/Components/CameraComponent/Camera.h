//==============================================================================
// File        : Camera.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-12-08
//------------------------------------------------------------------------------
// Overview :
// Camera クラスはシーン内の視点（カメラ）を管理するコンポーネントです。
// ビュー行列と投影行列を保持し、Perspective（透視投影）とOrthographic（正射影）の切り替えが可能です。
// Awake() で初期投影行列を設定し、Update() でカメラの動きやビュー行列を更新します。
// これにより、3D/2D 空間でのシーン描画に必要な視点変換を統合的に提供します。
//==============================================================================
#ifndef CAMERA_H
#define CAMERA_H

#include "Behaviour.h"
#include "MathTransform.h"
#include "GameObject.h"

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
		math::vector3f m_Rotation{};

		math::vector4f m_FrustumPlanes[6]; // 左, 右, 下, 上, 近, 遠

	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual void Awake() override {
			// 初期投影行列の設定
			if (m_ProjectionType == ProjectionType::Perspective) {
				SetPerspective(m_FOVY, m_AspectRatio, m_NearZ, m_FarZ);
			}
			else {
				SetOrthographic(m_OrthoWidth, m_OrthoHeight, m_NearZ, m_FarZ);
			}
		}
		virtual void Update() override = 0;
		void UpdateView(const math::vector3f& position, const math::vector3f& lookAt) {
			m_View = math::matrix::LookAtLH(position, lookAt, math::up());
			m_ViewProjection = m_View * m_Projection;
			ExtractFrustumPlanes();
		}

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
		virtual void SetPitch(float pitch) { m_Rotation.x = pitch; }
		virtual void SetYaw(float yaw) { m_Rotation.y = yaw; }
		virtual void SetRoll(float roll) { m_Rotation.z = roll; }

		// --- 方向ベクトル取得（共通処理）---
		math::vector3f GetForward() const {
			math::matrix rotation = math::matrix::Rotation(m_Rotation);
			math::vector3f forward = rotation.TransformVector(-math::forward());
			forward.normalize();
			return forward;
		}

		math::vector3f GetBackward() const {
			return -GetForward();
		}

		math::vector3f GetLeft() const {
			math::vector3f left = math::up().cross(-GetForward());
			left.normalize();
			return left;
		}

		math::vector3f GetRight() const {
			return -GetLeft();
		}

		virtual const math::matrix& GetView() const { return m_View; }
		virtual const math::matrix& GetProjection() const { return m_Projection; }
		virtual math::matrix GetViewProjection() const { return m_ViewProjection; }

		virtual void ExtractFrustumPlanes();
		virtual bool IsSphereVisible(const math::vector3f& center, float radius) const;
	};
} // namespace Framework


#endif // CAMERA_H
